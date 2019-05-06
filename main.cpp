#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <core/base_math.h>

#include <resource/resource_mgr.h>
#include <scene/camera.h>
#include <scene/light.h>

#include <iostream>

#include <render/renderer.h>
#include <glm/gtc/matrix_transform.hpp>
#include "core/timer.h"
#include <core/log.h>

#include <scene/model.h>


using namespace std;

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;


    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }


    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    glewInit();

    ResourceMgr::RegisterLoaders();
    ResourceMgr::PreCacheShader();
    Timer::Initialize();
    
    SceneNode* root = new SceneNode();

    Camera* camera = new Camera();
    camera->SetLocPosition(0, 0, -50);
    camera->SetPerspective(glm::radians(45.0f), 640.0f / 480.0f, 0.1f, 1000.0f);

    Light* light = new Light;
    light->SetParent(root);
    

    SceneNode* node;

    {
        // animation
        // node = Resource::LoadModel("data/model/astroBoy_walk_Maya.dae");
        // // SceneNode* node = Resource::LoadModel("data/model/rotation_2.dae");
        // node->SetParent(root);
        // node->Translate(glm::vec3(0, -10, -50));
        // node->SetLocScale(glm::vec3(1, 1, 1));
        // logConsole.PrintTree(node);
    }

    {
        Texture2D* texObj = ResourceMgr::Load<Texture2D>("data/model/utc_all2_light.png");
        texObj->Use();

        // Image* image = ResourceMgr::Load<Image>("data/model/utc_all2_light.png");

        node = ResourceMgr::LoadModel("data/model/SD_unitychan_humanoid.fbx");

        Model* model = node->FindNodeByName("_face")->As<Model>();
        model->GetMaterial()->SetTexture("diffuseTex", 0,  texObj);

        model = node->FindNodeByName("_head")->As<Model>();
        model->GetMaterial()->SetTexture("diffuseTex", 0, texObj);

        model = node->FindNodeByName("_body")->As<Model>();
        model->GetMaterial()->SetTexture("diffuseTex", 0, texObj);

        model = node->FindNodeByName("_Fhair")->As<Model>();
        model->GetMaterial()->SetTexture("diffuseTex", 0, texObj);

        model = node->FindNodeByName("_eye")->As<Model>();
        model->GetMaterial()->SetTexture("diffuseTex", 0, texObj);

        model = node->FindNodeByName("_Fhair2")->As<Model>();
        model->GetMaterial()->SetTexture("diffuseTex", 0, texObj);

        //logConsole.PrintTree(node);
        node->SetParent(root);
        node->Translate(glm::vec3(0, -10, 0));
        node->Scale(0.25, 0.25, 0.25);
        node->SetLocRotation(glm::angleAxis(glm::radians(180.0f), glm::vec3(0.0, 1.0, 0.0)));
    }

    // SceneNode* plane = Resource::LoadModel("data/model/plane.obj");
    // plane->SetParent(root);
    // plane->Translate(glm::vec3(0, -10, -50));
    // plane->Scale(10, 1, 10);

    // node->Rotate(45, glm::vec3(1, 1, 0));

	glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, 640, 480);

    // glm::mat4 mat(1.0);
    // mat = glm::rotate(mat, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    // glm::vec4 yAxis = mat * glm::vec4(0.0, 1.0, 0.0, 0.0);
    // mat = glm::rotate(mat, glm::radians(30.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    // mat = glm::rotate(mat, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    // glm::vec4 zAxis = mat * glm::vec4(0.0, 0.0, 1.0, 0.0);

    /* Loop until the user closes the window */


    while (!glfwWindowShouldClose(window)) 
    {
        /* Poll for and process events */
        glfwPollEvents();

        Timer::Update();

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // shader->Bind();
        // cout << startRot << endl;
        
        light->Rotate(0.0, 1.0f * Timer::GetDeltaTime(), 0.0f);
        // node->Rotate(0.5, glm::vec3(0, 1, 0));
        // root->Update();

        gRenderer.RenderScene(root, camera);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}