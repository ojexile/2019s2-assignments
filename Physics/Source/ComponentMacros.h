#pragma once
#include <vector>
#define TRANS GetComponent<TransformComponent>()
#define RENDER GetComponent<RenderComponent>()
#define CAMERA GetComponent<CameraComponent>()

typedef std::vector<unsigned char> _heightmap;