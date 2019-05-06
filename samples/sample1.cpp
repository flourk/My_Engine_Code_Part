#include <scene/app.h>

#include <scene/camera.h>
#include <scene/light.h>
#include <render/renderer.h>
#include <scene/model.h>

#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" ) 


class Sample1 : public App {
protected:
    virtual void OnInit() override;
    virtual void OnUpdate() override;
private:
    SceneNode* m_root;
    Camera* m_camera;
    Light* m_light;
};


void Sample1::OnInit()
{
    glClearColor(102.0f / 255.0f, 204.0f / 255.0f, 1.0f, 1.0f);

    m_root = new SceneNode();

    m_camera = new Camera();
    m_camera->SetLocPosition(0, 0, -50);
    m_camera->SetPerspective(glm::radians(45.0f), (float)m_width / m_height, 0.1f, 1000.0f);

    m_light = new Light;
    m_light->SetParent(m_root);

    SceneNode* node;

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
    node->SetParent(m_root);
    node->Translate(glm::vec3(0, -10, 0));
    node->Scale(0.25, 0.25, 0.25);
    node->SetLocRotation(glm::angleAxis(glm::radians(180.0f), glm::vec3(0.0, 1.0, 0.0)));

}

void Sample1::OnUpdate()
{
    glEnable(GL_DEPTH_TEST);
    // m_light->Rotate(0.0, 1.0f * Timer::GetDeltaTime(), 0.0f);
     m_root->Rotate(0.5, glm::vec3(0, 1, 0));

    gRenderer.RenderScene(m_root, m_camera);
}

void main()
{
    Sample1 app;
    app.Init("Sample1 - Lambert");
    app.Run();
    app.Destory();

}