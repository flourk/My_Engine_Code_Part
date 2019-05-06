#pragma once
#include <qopenglwidget.h>
#include <qopenglfunctions_4_4_core.h>
#include <scene/camera.h>
#include <scene/scene_node.h>

class OpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions_4_4_Core {
Q_OBJECT
public:
    OpenGLWidget(QWidget* parent = 0);

    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    void teardownGL();

signals:
    void loadedModel(SceneNode* node);

private:
    Camera* m_camera;
    SceneNode* m_root;
};