#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "resource_mgr.h"
#include "scene/model.h"
#include "scene/skinned_model.h"
#include <map>
#include <string>

#include <glm/glm.hpp>
#include "animation.h"
#include "assimp_to_glm.h"
#include <iostream>

#include <core/log.h>
#include <filesystem/path.h>

#include <shader_parser/shader_compiler.h>

using namespace std;

std::map<LoadFileType, IResourceLoader*> ResourceMgr::m_loaders;


void AddNodesToSkeleton(const aiNode* node, Skeleton& skeleton, int parentId, int depth)
{

    Bone newBone;
    newBone.name = node->mName.C_Str();
    newBone.parentId = parentId;

    skeleton.bones.push_back(newBone);

    // logConsole << "(resource_mgr)" << __FUNCTION__;
    // for(int i = 0; i < depth + 1; i++)
    // {
    //     cout << "  ";
    // }
    // std::cout << newBone.name << "   id: "  << (skeleton.bones.size() - 1) << "  parentId: " << parentId << std::endl;

    int id = skeleton.bones.size() - 1;
    for(unsigned i = 0; i < node->mNumChildren; i++)
    {
        // AddNodesToSkeleton(node->mChildren[i], skeleton, parentId + 1);
        AddNodesToSkeleton(node->mChildren[i], skeleton, id, depth + 1);
    }
}

void LoadSkeleton(const aiScene* scene, Skeleton& skeleton)
{
    AddNodesToSkeleton(scene->mRootNode, skeleton, -1, -1);
}


void LoadAnimations(const aiScene* pScene, std::vector<Animation>& animations)
{
    for(unsigned i = 0; i < pScene->mNumAnimations; i++)
    {
        Animation animation;
        const aiAnimation* aiAnim = pScene->mAnimations[i];

        animation.duration = aiAnim->mDuration;
        animation.tickPerSecond = aiAnim->mTicksPerSecond;


        for(unsigned j = 0; j < aiAnim->mNumChannels; j++)
        {
            const aiNodeAnim* aiChannel = aiAnim->mChannels[j];
            AnimationNode animationNode;
            animationNode.name = aiChannel->mNodeName.C_Str();
            // cout << aiChannel->mNodeName.C_Str() << endl;

            for(unsigned k = 0; k < aiChannel->mNumPositionKeys; k++)
            {
                PositionKey positionKey;
                positionKey.time = (float) aiChannel->mPositionKeys[k].mTime;
                positionKey.value =  AssimpToGLM::aiToGLM(aiChannel->mPositionKeys[k].mValue);
                animationNode.positionkeys.push_back(positionKey);
            }

            for(unsigned k = 0; k < aiChannel->mNumRotationKeys; k++)
            {
                RotationKey rotationKey;
                rotationKey.time = (float) aiChannel->mRotationKeys[k].mTime;
                rotationKey.value = AssimpToGLM::aiToGLM(aiChannel->mRotationKeys[k].mValue);
                animationNode.rotationKeys.push_back(rotationKey);
            }

            animation.nodes.push_back(animationNode);
        }

        animations.push_back(animation);

    }
}


void LoadBones(const aiScene* scene, Skeleton& skeleton)
{
    for(unsigned i = 0; i < scene->mNumMeshes; i++)
    {
        const aiMesh* mesh = scene->mMeshes[i];
        for(unsigned j = 0; j < mesh->mNumBones; j++)
        {
            const aiBone* boneNode = mesh->mBones[j];
            std::string boneName = mesh->mBones[j]->mName.C_Str();

            Bone* bone = skeleton.FindBone(boneName);
            if(bone)
            {
                bone->offsetMatrix = AssimpToGLM::aiToGLM(boneNode->mOffsetMatrix);
                // std::cout << boneName << std::endl;
                // logConsole << bone->offsetMatrix;

            }
        }
    }
}

void LoadBoneVertexInfos(const aiMesh* modelMesh,std::vector<Vertex>& vertices, const Skeleton& skeleton)
{
    static const int WEIGHTS_PER_VERTEX = 4;

    int boneArraysSize = modelMesh->mNumVertices * WEIGHTS_PER_VERTEX;

    std::vector<int> boneIDs;
    boneIDs.resize(boneArraysSize);
    std::vector<float> boneWeights;
    boneWeights.resize(boneArraysSize);

    for(unsigned i=0; i< modelMesh->mNumBones; i++)
    {
        aiBone* aiBone = modelMesh->mBones[i];

        for(unsigned j=0; j<aiBone->mNumWeights; j++)
        {
            aiVertexWeight weight = aiBone->mWeights[j];
            unsigned vertexStart = weight.mVertexId * WEIGHTS_PER_VERTEX;

            for(int k=0; k < WEIGHTS_PER_VERTEX; k++)
            {
               if(boneWeights.at(vertexStart+k) == 0)
               {
                    boneWeights.at(vertexStart+k) = weight.mWeight;
                    boneIDs.at(vertexStart+k) = i;
                    std::string name(aiBone->mName.C_Str());
                    vertices.at(weight.mVertexId).boneIndices[k] = (float) skeleton.FindBoneIndex(name);
                    vertices.at(weight.mVertexId).boneWeights[k] = weight.mWeight;
                    break;
               }
            }
        }
    }
}
    
void ProcessMesh(const aiMesh* modelMesh, const aiScene* scene, Mesh* mesh, const Skeleton& skeleton, bool& hasBone)
{
    // stringstream ss;
    hasBone = false;

    if(!modelMesh->mNumVertices)
        return;

    std::vector<Vertex> vertices;
    std::vector<int> indices;

    for(unsigned i = 0; i < modelMesh->mNumVertices; i++)
    {
        Vertex vtx;
        if(modelMesh->HasPositions())
        {
            vtx.position.x = modelMesh->mVertices[i].x;
            vtx.position.y = modelMesh->mVertices[i].y;
            vtx.position.z = modelMesh->mVertices[i].z;
        }

        if(modelMesh->HasNormals())
        {
            vtx.normal.x = modelMesh->mNormals[i].x;
            vtx.normal.y = modelMesh->mNormals[i].y;
            vtx.normal.z = modelMesh->mNormals[i].z;
        }

        if(modelMesh->HasTextureCoords(0))
        {
            vtx.uv.x = modelMesh->mTextureCoords[0][i].x;
            vtx.uv.y = modelMesh->mTextureCoords[0][i].y;
        }

        vertices.push_back(vtx);
    }

    if(modelMesh->HasBones())
    {
        hasBone = true;
        LoadBoneVertexInfos(modelMesh, vertices, skeleton);
    }

    for(unsigned i = 0; i < modelMesh->mNumFaces; i++)
    {
        const aiFace& face = modelMesh->mFaces[i];
        for(unsigned j = 0; j < face.mNumIndices; j++)
        {
            indices.push_back(face.mIndices[j]);
        }
    }

    mesh->SetData(vertices, indices);
}

SceneNode* ProcessNode(const aiNode* node, const aiScene* scene, Skeleton& skeleton, std::vector<Animation>& anims)
{
    std::vector<Mesh*> meshes;
    bool hasBone = false;
    for(unsigned i = 0; i < node->mNumMeshes; i++)
    {
        Mesh* mesh = new Mesh;
        const aiMesh* modelMesh = scene->mMeshes[node->mMeshes[i]];
        ProcessMesh(modelMesh, scene, mesh, skeleton, hasBone);
        meshes.emplace_back(mesh);
    }


    // make new scene node
    SceneNode* sceneNode = nullptr;
    if(hasBone)
    {
        SkinnedModel* model = new SkinnedModel;
        
        Ref<Material> material(new Material);
        material->SetShader(ResourceMgr::GetShader("skin"));
        model->SetMaterial(material);
        model->SetMeshes(meshes);
        model->SetSkeleton(skeleton);
        if(anims.size() > 0)
            model->SetAnimation(anims[0]);
        sceneNode = model;
    }
    else if(node->mNumMeshes > 0)
    {
        Model* model = new Model;
        Ref<Material> material(new Material);
        material->SetShader(ResourceMgr::GetShader("base"));
        model->SetMaterial(material);
        model->SetMeshes(meshes);
        sceneNode = model;
    }
    else
    {
        sceneNode = new SceneNode;
    }

    // set scene node preporty
    sceneNode->mName = node->mName.C_Str();
    aiVector3D pos, scale;
    aiQuaternion rot;

    node->mTransformation.Decompose(scale, rot, pos);
    sceneNode->SetLocPosition(AssimpToGLM::aiToGLM(pos));
    sceneNode->SetLocRotation(AssimpToGLM::aiToGLM(rot));
    sceneNode->SetLocScale(AssimpToGLM::aiToGLM(scale));


    for(unsigned i = 0; i < node->mNumChildren; i++)
    {
        SceneNode* childSceneNode = ProcessNode(node->mChildren[i], scene, skeleton, anims);
        childSceneNode->SetParent(sceneNode);
    }

    return sceneNode;
}

SceneNode* ResourceMgr::LoadModel(const char* name)
{
    Assimp::Importer importer;

    const aiScene* scene = importer.ReadFile(name, aiProcess_FlipUVs | aiProcess_Triangulate);

    Skeleton skeleton;
    LoadSkeleton(scene, skeleton);

    LoadBones(scene, skeleton);

    std::vector<Animation> anims;
    LoadAnimations(scene, anims);

    SceneNode* sceneNode = ProcessNode(scene->mRootNode, scene, skeleton, anims);

    return sceneNode;
}


////////////////// shader
std::map<std::string, Shader*> ResourceMgr::m_shaderCache;

Shader* ResourceMgr::GetShader(const char* name)
{
    auto findIt = m_shaderCache.find(name);
    if(findIt != m_shaderCache.end())
    {
        return findIt->second;
    }

    return nullptr;
}


void ResourceMgr::PreCacheShader()
{
    ShaderCompiler compiler;
    logConsole << "Loading base";
    Shader* baseShader = compiler.Compile("data/shader/base.fxc");
    m_shaderCache.insert(std::make_pair("base", baseShader));

    logConsole << "Loading skin";
    Shader* skinShader = compiler.Compile("data/shader/skin.fxc");
    m_shaderCache.insert(std::make_pair("skin", skinShader));

    logConsole << "Loading toon";
    Shader* toonShader = compiler.Compile("data/shader/toon.fxc");
    m_shaderCache.insert(std::make_pair("toon", toonShader));

    logConsole << "Loading unlit";
    Shader* unlitShader = compiler.Compile("data/shader/unlit.fxc");
    m_shaderCache.insert(std::make_pair("unlit", unlitShader));
}

/////////// loader
void ResourceMgr::RegisterLoaders()
{
    ImageLoader::RegisterToMgr();
    TextureLoader::RegisterToMgr();
}


void ResourceMgr::AddLoader(LoadFileType fileType, IResourceLoader* loader)
{
    m_loaders.insert(make_pair(fileType, loader));
}

Resource* ResourceMgr::Load(const String& path, ILoadOption* option)
{
    if(!option)
    {
        const String ext = Path::GetExt(path);
        for(auto& loaderPair : m_loaders)
        {
            auto& loader = loaderPair.second;
            loader->IsSupported(ext);
            return loader->Load(path, option);
        }

        return nullptr;
    }
    else
    {
        auto it = m_loaders.find(option->loadType);
        if(it == m_loaders.end())
            return nullptr;

        return it->second->Load(path, option);
    }
}
