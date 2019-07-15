#include "DataContainer.h"
#include "ChengRigidbody.h"
#include "BallScript.h"
#include "BulletScript.h"
#include "ParticleScript.h"
#include "ParticleSpawnerScript.h"
#include "RainScript.h"
DataContainer::DataContainer()
{
	// Meshes================================================================================
	m_map_Meshes["ground"] = MeshBuilder::GenerateQuad("ground", { 1.f,1.f,1.f }, 500);
	m_map_Meshes["ball"] = MeshBuilder::GenerateSphere("ball", Color(1, 0, 0), 10, 10, 1.f);
	m_map_Meshes["ball2"] = MeshBuilder::GenerateSphere("ball", Color(0, 0, 1), 10, 10, 1.f);
	m_map_Meshes["ball3"] = MeshBuilder::GenerateSphere("ball", Color(0, 1, 0), 10, 10, 1.f);
	m_map_Meshes["pillar"] = MeshBuilder::GenerateOBJ("pillar", "cylinder");
	m_map_Meshes["wall"] = MeshBuilder::GenerateCube("wall", Color((float)0.2, (float)0.2, (float)0.2), 1.f);
	m_map_Meshes["square"] = MeshBuilder::GenerateCube("wall", Color((float)0.5, (float)0.5, (float)0.5), 1.f);
	m_map_Meshes["ceil"] = MeshBuilder::GenerateCube("wall", Color((float)0.9, (float)0.9, (float)0.9), 1.f);
	m_map_Meshes["floor"] = MeshBuilder::GenerateCube("wall", Color((float)0.8, (float)0.8, (float)0.8), 1.f);
	// Meshs--------------------------------------------------------------------------------
	m_map_Meshes["Quad"] = MeshBuilder::GenerateQuad("Quad", { 1,1,1 }, 5);
	//m_map_Meshes["CUBE"] = MeshBuilder::GenerateCube("CUBE", { 0,1,1 }, 10);
	m_map_Meshes["Cube"] = MeshBuilder::GenerateOBJ("cubeobj", "Objects/cube.obj");
	m_map_Meshes["Cube"]->m_uTextureArray[0] = LoadTGA("textures/cube.tga");
	m_map_Meshes["Cube"]->m_uTextureArray[1] = LoadTGA("textures/moss1.tga");

	m_map_Meshes["Ground"] = MeshBuilder::GenerateQuad("Ground", { 1.f,1.f,1.f }, 500);
	// Gun
	m_map_Meshes["Gun"] = MeshBuilder::GenerateQuad("QUAD", { 1,1,1 }, 1000.f);
	m_map_Meshes["Gun"]->m_uTextureArray[0] = LoadTGA("textures/PLAYER_PISTOL.tga");

	//m_map_Meshes["GROUND"]->m_uTextureArray[0] = 1;

	//--------------------------------------------------------------------------------
	// Gameobjects================================================================================
	GameObject* ball = new GameObject;
	m_map_GO["ball"] = ball;
	ball->AddComponent(new RenderComponent(this->GetMesh("ball")));
	ball->AddComponent(new ChengRigidbody(ChengRigidbody::BALL));
	ball->AddComponent(new BallScript());
	// --------------------------------------------------------------------------------
	GameObject * ball2 = new GameObject;
	m_map_GO["ball2"] = ball2;
	ball2->AddComponent(new RenderComponent(this->GetMesh("ball2")));
	ball2->AddComponent(new ChengRigidbody(ChengRigidbody::BALL));
	// --------------------------------------------------------------------------------
	GameObject* go = new GameObject;
	m_map_GO["ball3"] = go;
	go->AddComponent(new RenderComponent(this->GetMesh("ball3")));
	go->AddComponent(new ChengRigidbody(ChengRigidbody::BALL));
	// --------------------------------------------------------------------------------
	GameObject* wall = new GameObject;
	m_map_GO["wall"] = wall;

	wall->GetComponent<TransformComponent>()->SetRotation(-90, 0, 1, 0);
	wall->AddComponent(new RenderComponent(this->GetMesh("wall")));
	wall->AddComponent(new ChengRigidbody(ChengRigidbody::WALL));
	// --------------------------------------------------------------------------------
	wall = new GameObject;
	m_map_GO["ceil"] = wall;

	wall->GetComponent<TransformComponent>()->SetRotation(-90, 0, 1, 0);
	wall->AddComponent(new RenderComponent(this->GetMesh("ceil")));
	wall->AddComponent(new ChengRigidbody(ChengRigidbody::WALL));
	// --------------------------------------------------------------------------------
	GameObject* square = new GameObject;
	m_map_GO["square"] = square;

	square->AddComponent(new RenderComponent(this->GetMesh("square")));
	square->AddComponent(new ChengRigidbody(ChengRigidbody::SQUARE));
	// --------------------------------------------------------------------------------
	GameObject* floor = new GameObject;
	m_map_GO["floor"] = floor;
	m_map_Animated["Leaf"] = MeshBuilder::GenerateAnimatedMesh("Leaf", 4, 4, 0, 15, 2.f, true);
	m_map_Animated["Leaf"]->m_Mesh->m_uTextureArray[0] = LoadTGA("textures/Leaf.tga");

	m_map_Meshes["Water"] = MeshBuilder::GenerateQuad("TestParticle", { 1.f,1.f,1.f }, 0.4f);
	m_map_Meshes["Water"]->m_uTextureArray[0] = LoadTGA("textures/particle.tga");

	m_map_Animated["Smoke"] = MeshBuilder::GenerateAnimatedMesh("Smoke", 5, 8, 0, 39, 2.f, false);
	m_map_Animated["Smoke"]->m_Mesh->m_uTextureArray[0] = LoadTGA("textures/Smoke.tga");

	m_map_Meshes["Fish"] = MeshBuilder::GenerateQuad("TestParticle", { 1.f,1.f,1.f }, 1.1f);
	m_map_Meshes["Fish"]->m_uTextureArray[0] = LoadTGA("textures/Fish.tga");

	m_map_Meshes["Droplet"] = MeshBuilder::GenerateQuad("TestParticle", { 1.f,1.f,1.f }, 1.2f);
	m_map_Meshes["Droplet"]->m_uTextureArray[0] = LoadTGA("textures/particle.tga");

	m_map_Meshes["DropletMini"] = MeshBuilder::GenerateQuad("TestParticle", { 1.f,1.f,1.f }, 0.2f);
	m_map_Meshes["DropletMini"]->m_uTextureArray[0] = LoadTGA("textures/particle.tga");

	m_map_Meshes["WaterPlane"] = MeshBuilder::GenerateOBJ("cubeobj", "Objects/water.obj");
	m_map_Meshes["WaterPlane"]->m_uTextureArray[0] = LoadTGA("textures/water.tga");

	m_map_Meshes["Tree"] = MeshBuilder::GenerateOBJ("cubeobj", "Objects/tree.obj");
	m_map_Meshes["Tree"]->m_uTextureArray[0] = LoadTGA("textures/tree.tga");
	m_map_Meshes["Tree"]->m_uTextureArray[1] = LoadTGA("textures/moss1.tga");

	m_map_Meshes["Crosshair"] = MeshBuilder::GenerateQuad("Crosshair", { 1.f,1.f,1.f }, 2);
	m_map_Meshes["Crosshair"]->m_uTextureArray[0] = LoadTGA("textures/Crosshair.tga");
	//--------------------------------------------------------------------------------
	// Gameobjects--------------------------------------------------------------------------------
	// Particle
	GameObject* SmokeParticle = new GameObject;
	SmokeParticle->AddComponent(new RenderComponent(this->GetAnimation("Smoke")));
	SmokeParticle->GetComponent<RenderComponent>()->SetBillboard(true);
	SmokeParticle->AddComponent(new ParticleScript(2.f, { 0,0.01f,0 }, { 0,0,0 }, { 0,0,0 }, { -0.8f,-0.8f,0 }, {}));
	m_map_GO["SmokeParticle"] = SmokeParticle;

	//
	// Fish
	GameObject* Fish = new GameObject;
	Fish->AddComponent(new RenderComponent(this->GetMesh("Fish")));
	Fish->GetComponent<RenderComponent>()->SetBillboard(true);
	Fish->AddComponent(new ParticleScript(5.0f, { 0.15f,0.4f,0.0f }, { 0,0,0 }, { 0,-1.f,0 }, { -0.5,-0.5f,0 }, { 0,0,0 }));
	m_map_GO["Fish"] = Fish;
	//
	// Droplet
	GameObject* Droplet = new GameObject;
	Droplet->AddComponent(new RenderComponent(this->GetMesh("Droplet")));
	Droplet->GetComponent<RenderComponent>()->SetBillboard(true);
	Droplet->AddComponent(new ParticleScript(5.0f, { 0.2f,0.5f,0.2f }, { 0,0,0 }, { 0,-1.f,0 }, { -0.5,-0.5f,0 }, { 1,0,1 }));
	m_map_GO["Droplet"] = Droplet;
	//
	// DropletMini
	GameObject* DropletMini = new GameObject;
	DropletMini->AddComponent(new RenderComponent(this->GetMesh("DropletMini")));
	DropletMini->GetComponent<RenderComponent>()->SetBillboard(true);
	DropletMini->AddComponent(new ParticleScript(5.0f, { 0.3f,0.4f,0.3f }, { 0,0,0 }, { 0,-1.f,0 }, { -0.5,-0.5f,0 }, { 1,0,1 }));
	m_map_GO["DropletMini"] = DropletMini;
	//
	// Leaf
	GameObject* Leaf = new GameObject;
	Leaf->AddComponent(new RenderComponent(this->GetAnimation("Leaf")));
	Leaf->GetComponent<RenderComponent>()->SetBillboard(true);
	Leaf->AddComponent(new ParticleScript(6.5f, { 0,-0.2f,0 }, { 2,0,0 }, { 0,0.01f,0 }, { -0.01f,-0.01f,0 }, {}));
	m_map_GO["Leaf"] = Leaf;
	//
	// Spawner
	GameObject* Spawner = new GameObject;
	Spawner->AddComponent(new ParticleSpawnerScript(this->GetGameObject("SmokeParticle"), 0.01f, { .5f,.5f,.5f }, .8f, "Smoke"));
	//
	// Fountain Spawner
	GameObject* Fountain = new GameObject;
	//Fountain->GetChildList<TransformComponent>()->SetPosition(-39, 0, 0);
	Fountain->AddComponent(new ParticleSpawnerScript(this->GetGameObject("DropletMini"), 0.05f, { 0,0,0 }, .2f, "Default", 0.4f));
	m_map_GO["Fountain"] = Fountain;
	//
	// Rain
	GameObject* Rain = new GameObject;
	Rain->AddComponent(new RenderComponent(this->GetMesh("Water")));
	Rain->GetComponent<RenderComponent>()->SetBillboard(true);
	Rain->AddComponent(new ParticleScript(4.0f, { 0,-0.7f,0 }, { 0,0,0 }, { 0,0,0 }, { 0.0f,0,0 }, {}));
	Rain->AddComponent(new RainScript(this->GetGameObject("Fountain")));
	m_map_GO["Rain"] = Rain;

	//Bullet
	GameObject* bullet = new GameObject();
	bullet->AddComponent(new RenderComponent(this->GetMesh("Cube")));
	bullet->GetComponent<TransformComponent>()->SetScale(0.1f, 0.1f, 0.1f);
	bullet->GetComponent<RenderComponent>()->SetLightEnabled(true);
	bullet->GetComponent<RenderComponent>()->SetBillboard(true);
	bullet->AddComponent(new BulletScript(1.f));
	bullet->AddChild(Spawner);
	m_map_GO["Bullet"] = bullet;
	//
	floor->GetComponent<TransformComponent>()->SetRotation(-90, 0, 1, 0);
	floor->AddComponent(new RenderComponent(this->GetMesh("floor")));
	floor->AddComponent(new ChengRigidbody(ChengRigidbody::BOX));
	//--------------------------------------------------------------------------------
	GameObject* pillar = new GameObject;
	m_map_GO["pillar"] = pillar;
	pillar->AddComponent(new RenderComponent(this->GetMesh("pillar")));
	pillar->AddComponent(new ChengRigidbody(ChengRigidbody::PILLAR));
	//wall->GetComponent<ChengRigidbody>()->SetNormal({ 0, 0, -1 });
	// Shaders================================================================================
	m_map_Shaders["Default"] = LoadShaders("Shadow", "Shadow");

	m_map_Shaders["GPass"] = LoadShaders("GPass", "GPass");
	// Shaders--------------------------------------------------------------------------------
	m_map_Shaders["Default"] = LoadShaders("Shader//Shadow/Shadow.vertexshader", "Shader//Shadow/Shadow.fragmentshader");
	m_map_Shaders["Water"] = LoadShaders("Shader//water.vertexshader", "Shader//water.fragmentshader");
	m_map_Shaders["GPass"] = LoadShaders("Shader//shadow/GPass.vertexshader", "Shader//shadow/GPass.fragmentshader");
	m_map_Shaders["Smoke"] = LoadShaders("Shader//Smoke.vertexshader", "Shader//Smoke.fragmentshader");
	m_map_Shaders["Underwater"] = LoadShaders("Shader//Underwater.vertexshader", "Shader//Underwater.fragmentshader");
	//--------------------------------------------------------------------------------
}

DataContainer::~DataContainer()
{
	std::map<std::string, Mesh*>::iterator it;
	for (it = m_map_Meshes.begin(); it != m_map_Meshes.end(); it++)
	{
		// it->first == key
		// it->second == value
		delete it->second;
	}
	m_map_Meshes.clear();
	std::map<std::string, AnimatedMesh*>::iterator it2;
	for (it2 = m_map_Animated.begin(); it2 != m_map_Animated.end(); it2++)
	{
		// it->first == key
		// it->second == value
		delete it2->second;
	}
	m_map_Animated.clear();
	std::map<std::string, GameObject*>::iterator it3;
	for (it3 = m_map_GO.begin(); it3 != m_map_GO.end(); it3++)
	{
		// it->first == key
		// it->second == value
		delete it3->second;
	}
	m_map_GO.clear();
}

Mesh* DataContainer::GetMesh(std::string name)
{
	Mesh* mesh = m_map_Meshes[name];
	if (!mesh)
		DEFAULT_LOG("ERROR: Mesh not found of name: " + name);
	return mesh;
}
AnimatedMesh* DataContainer::GetAnimation(std::string name)
{
	AnimatedMesh* mesh = m_map_Animated[name];
	if (!mesh)
		DEFAULT_LOG("ERROR: Animation not found of name: " + name);
	return mesh;
}
GameObject* DataContainer::GetGameObject(std::string name)
{
	GameObject* go = m_map_GO[name];
	if (!go)
		DEFAULT_LOG("ERROR: GameObject not found of name: " + name);
	return go;
}
unsigned DataContainer::GetShader(std::string key)
{
	if (m_map_Shaders.count(key) <= 0)
		DEFAULT_LOG("ERROR: Shader not found of name: " + key);
	unsigned shader = m_map_Shaders[key];
	return shader;
}