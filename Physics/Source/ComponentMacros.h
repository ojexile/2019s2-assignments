#pragma once
#include <vector>

#define TRANS GetComponent<TransformComponent>()
#define RENDER GetComponent<RenderComponent>()
#define CAMERA GetComponent<CameraComponent>()
#define RIGID GetComponent<ChengRigidBody>()
#define CONSTRAIN GetComponent<Constrain>()

typedef std::vector<unsigned char> _heightmap;