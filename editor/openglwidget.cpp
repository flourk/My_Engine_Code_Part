#include <GL/glew.h>
#include "openglwidget.h"
#include <resource/resource.h>


OpenGLWidget::OpenGLWidget(QWidget* parent) : QOpenGLWidget(parent)
{

}

void OpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glewInit();

    Resource::PreCacheShader();

    m_camera = new Camera();
    m_camera->SetPerspective(glm::radians(45.0f), 640.0f / 480.0f, 0.1f, 1000.0f);

    m_root = new SceneNode();
    m_root->mName = "Root";

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
        node = Resource::LoadModel("data/model/SD_unitychan_humanoid.fbx");

        node->SetParent(m_root);
        node->Translate(glm::vec3(0, -10, -50));
        node->Scale(0.5, 0.5, 0.5);
//        node->Rotate(0, 0, 0);
        // node->Rotate(0, 20, 0);
       node->GetChildren()[1]->Rotate(0, 20, 0);
    }

    emit loadedModel(m_root);
}


void OpenGLWidget::resizeGL(int width, int height)
{

}

void OpenGLWidget::paintGL()
{
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_root->Render(m_camera);
}