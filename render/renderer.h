#pragma once

#include "pass.h"

class SceneNode;
class Camera;
class Parameter;

class Renderer {
public:
    void RenderScene(SceneNode* rootNode, Camera* camera);

    void SetPass(const Pass& pass, const Parameter& param);


private:
};

extern Renderer gRenderer;