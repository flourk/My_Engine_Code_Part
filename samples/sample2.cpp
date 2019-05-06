#include <scene/app.h>

#include <scene/camera.h>
#include <scene/light.h>
#include <render/renderer.h>
#include <scene/model.h>

#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" ) 

class Sample2 : public App {
protected:
    virtual void OnInit() override;
    virtual void OnUpdate() override;
private:
    SceneNode* m_root;
    Camera* m_camera;
    Light* m_light;
};


void Sample2::OnInit()
{
    m_root = new SceneNode();

    m_camera = new Camera();
    m_camera->SetLocPosition(0, 0, -50);
    m_camera->SetPerspective(glm::radians(45.0f), (float)m_width / m_height, 0.1f, 1000.0f);

    m_light = new Light;
    m_light->SetParent(m_root);

    SceneNode* node;

    Texture2D* texObj = ResourceMgr::Load<Texture2D>("data/model/utc_all2_light.png");
    Texture2D* texDark = ResourceMgr::Load<Texture2D>("data/model/utc_all2_dark.png");


    // Image* image = ResourceMgr::Load<Image>("data/model/utc_all2_light.png");

    node = ResourceMgr::LoadModel("data/model/SD_unitychan_humanoid.fbx");

    static std::vector<const char*> useToons =
    {
        "_face", "_head", "_body", "_Fhair", "_Fhair2"
    };


    for(auto it = useToons.begin(); it != useToons.end(); it++)
    {
        const char* name = *it;

        Model* model = node->FindNodeByName(name)->As<Model>();
        model->GetMaterial()->SetShader(ResourceMgr::GetShader("toon"));
        //outline
        model->GetMaterial()->SetVec4f("outLineColor", Vec4f(0.0f, 0.0f, 0.0f, 1.0f));
        model->GetMaterial()->SetFloat("outlineWidth", 7.0f);
        //toon_forward
        model->GetMaterial()->SetTexture("mainTex", 0, texObj);
        model->GetMaterial()->SetTexture("the1stShadeMap", 1, texDark);
        model->GetMaterial()->SetVec4f("the1stColor", Vec4f(1.0, 1.0, 1.0, 1.0));
        model->GetMaterial()->SetFloat("useBaseAs1st", 0.0);
        model->GetMaterial()->SetVec4f("the2ndColor", Vec4f(1.0, 1.0, 1.0, 1.0));
        model->GetMaterial()->SetFloat("useThe1stAs2nd", 1.0);
        model->GetMaterial()->SetFloat("baseColorStep", 0.446f);
        model->GetMaterial()->SetFloat("baseShadeFeather", 0.235f);
        model->GetMaterial()->SetFloat("shadeColorStep", 0.438f);
        model->GetMaterial()->SetFloat("the1st2ndShadesFeather", 0.152f);

    }

    Model* model = node->FindNodeByName("_eye")->As<Model>();
    model->GetMaterial()->SetShader(ResourceMgr::GetShader("unlit"));
    model->GetMaterial()->SetTexture("diffuseTex", 0, texObj);

    // model = node->FindNodeByName("_face")->As<Model>();
    // model->GetMaterial()->SetTexture("diffuseTex", 0,  texObj);

    // model = node->FindNodeByName("_head")->As<Model>();
    // // model->GetMaterial()->SetShader(ResourceMgr::GetShader("toon"));
    // model->GetMaterial()->SetTexture("diffuseTex", 0, texObj);

    // model = node->FindNodeByName("_body")->As<Model>();
    // model->GetMaterial()->SetShader(ResourceMgr::GetShader("toon"));
    // //outline
    // model->GetMaterial()->SetVec4f("outLineColor", Vec4f(0.0f, 0.0f, 0.0f, 1.0f));
    // model->GetMaterial()->SetFloat("outlineWidth", 7.0f);
    // //toon_forward
    // model->GetMaterial()->SetTexture("mainTex", 0, texObj);
    // model->GetMaterial()->SetTexture("the1stShadeMap", 1, texDark);
    // model->GetMaterial()->SetVec4f("the1stColor", Vec4f(1.0, 1.0, 1.0, 1.0));
    // model->GetMaterial()->SetFloat("useBaseAs1st", 0.0);
    // model->GetMaterial()->SetVec4f("the2ndColor", Vec4f(1.0, 1.0, 1.0, 1.0));
    // model->GetMaterial()->SetFloat("useThe1stAs2nd", 1.0);
    // model->GetMaterial()->SetFloat("baseColorStep", 0.446f);
    // model->GetMaterial()->SetFloat("baseShadeFeather", 0.235f);
    // model->GetMaterial()->SetFloat("shaderColorStep", 0.438f);
    // model->GetMaterial()->SetFloat("the1st2ndShadesFeather", 0.152f);


    // model = node->FindNodeByName("_Fhair")->As<Model>();
    // // model->GetMaterial()->SetShader(ResourceMgr::GetShader("toon"));
    // model->GetMaterial()->SetTexture("diffuseTex", 0, texObj);



    // model = node->FindNodeByName("_Fhair2")->As<Model>();
    // // model->GetMaterial()->SetShader(ResourceMgr::GetShader("toon"));
    // model->GetMaterial()->SetTexture("diffuseTex", 0, texObj);

    //logConsole.PrintTree(node);
    node->SetParent(m_root);
    node->Translate(glm::vec3(0, -10, 0));
    node->Scale(0.25, 0.25, 0.25);
    node->SetLocRotation(glm::angleAxis(glm::radians(180.0f), glm::vec3(0.0, 1.0, 0.0)));

}

void Sample2::OnUpdate()
{
    glEnable(GL_DEPTH_TEST);
    glClearColor(102.0f / 255.0f, 204.0f / 255.0f, 1.0f, 1.0f);
    m_light->Rotate(0.0, 1.0f * Timer::GetDeltaTime(), 0.0f);
//    m_root->Rotate(0.5, glm::vec3(0, 1, 0));

    gRenderer.RenderScene(m_root, m_camera);
}

void main()
{
    Sample2 app;
    app.Init("Sample2 - Toon Shader");
    app.Run();
    app.Destory();

}