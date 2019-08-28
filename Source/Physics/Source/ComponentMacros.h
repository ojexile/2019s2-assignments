#pragma once
#include <vector>

#define GetComp(c) GetComponent<c>()
#define GC(c) GetComponent<c>()

#define TRANS GetComponent<TransformComponent>()
#define RENDER GetComponent<RenderComponent>()
#define CAMERA GetComponent<CameraComponent>()
#define RIGID GetComponent<Rigidbody>()
#define CONSTRAIN GetComponent<Constrain>()
#define AUGMENT GetComponent<Augment>()
#define PART GetComponent<WeaponPartScript>()
#define GUN GetComponent<GunScript>()
#define LOOT GetComponent<LootScript>()
#define PROJECTILE GetComponent<ProjectileScript>()
#define PARTICLE GetComponent<ParticleScript>()

typedef std::vector<unsigned char> _heightmap;