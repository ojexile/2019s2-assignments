#pragma once
#include <vector>

#define TRANS GetComponent<TransformComponent>()
#define RENDER GetComponent<RenderComponent>()
#define CAMERA GetComponent<CameraComponent>()
#define RIGID GetComponent<Rigidbody>()
#define CONSTRAIN GetComponent<Constrain>()
#define PART GetComponent<PartScript>()
#define MISCPART GetComponent<MiscellaneousPartScript>()
#define GUN GetComponent<GunScript>()
#define LOOT GetComponent<LootScript>()

typedef std::vector<unsigned char> _heightmap;