#pragma once
#include <vector>
#define TRANSFORM GetComponent<TransformComponent>()
#define RENDER GetComponent<RenderComponent>()
#define CAMERA GetComponent<CameraComponent>()

typedef std::vector<unsigned char> heightmap;