#pragma once
#include <vector>

#define TRANS GetComponent<TransformComponent>()
#define RENDER GetComponent<RenderComponent>()
#define CAMERA GetComponent<CameraComponent>()
#define RIGID GetComponent<ChengRigidBody>()
#define RIGID GetComponent<Constrain>()

typedef std::vector<unsigned char> _heightmap;