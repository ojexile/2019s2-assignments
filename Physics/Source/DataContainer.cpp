#include "DataContainer.h"
#include "ChengRigidbody.h"
#include "BallScript.h"
#include "BulletScript.h"
#include "ParticleScript.h"
#include "ParticleSpawnerScript.h"
#include "RainScript.h"
#include "GoalScript.h"
#include "BouncerScript.h"
#include "PaddleScript.h"
#include <time.h>
DataContainer::DataContainer()
{
	clock_t begin = clock();
	// Meshes================================================================================
	m_map_Meshes["Text"] = MeshBuilder::GenerateText("text", 16, 16);
	m_map_Meshes["Text"]->m_uTextureArray[0] = LoadTGA("calibri");

	m_map_Meshes["ground"] = MeshBuilder::GenerateQuad("ground", { 1.f,1.f,1.f }, 500);
	m_map_Meshes["ball"] = MeshBuilder::GenerateSphere("ball", Color(1, 1, 1), 10, 10, 1.f);
	//m_map_Meshes["ball2"] = MeshBuilder::GenerateSphere("ball", Color(0, 0, 1), 10, 10, 1.f);
	//m_map_Meshes["ball3"] = MeshBuilder::GenerateSphere("ball", Color(0, 1, 0), 10, 10, 1.f);

	m_map_Meshes["pillar"] = MeshBuilder::GenerateOBJ("cylinder");

	m_map_Meshes["paddle"] = MeshBuilder::GenerateOBJ("paddle");

	m_map_Meshes["wall"] = MeshBuilder::GenerateCube("wall", Color((float)0.2, (float)0.2, (float)0.2), 1.f);

	m_map_Meshes["square"] = MeshBuilder::GenerateCube("wall", Color((float)0.5, (float)0.5, (float)0.2), 1.f);

	m_map_Meshes["goal"] = MeshBuilder::GenerateCube("wall", Color((float)0.8, (float)0.2, (float)0.2), 1.f);

	m_map_Meshes["SkyPlane"] = MeshBuilder::GenerateSkyPlane("SkyPlane", { 0,0,1 }, 24, 52, 1000, 6, 6);
	m_map_Meshes["SkyPlane"]->m_uTextureArray[0] = LoadTGA("sky");

	Mesh* mesh = GenerateTerrain("Terrain", "heightmapMain", { 500,30,500 });
	mesh->m_uTextureArray[0] = LoadTGA("moss1");
	mesh->m_uTextureArray[1] = LoadTGA("sky");

	mesh = GenerateTerrain("Terrain", "heightmapFlat", { 500,30,500 });
	mesh->m_uTextureArray[0] = LoadTGA("moss1");
	mesh->m_uTextureArray[1] = LoadTGA("sky");

	m_map_Meshes["Gun"] = MeshBuilder::GenerateQuad("QUAD", { 1,1,1 }, 1000.f);
	m_map_Meshes["Gun"]->m_uTextureArray[0] = LoadTGA("PLAYER_PISTOL");

	//m_map_Meshes["Water"] = MeshBuilder::GenerateQuad("TestParticle", { 1.f,1.f,1.f }, 0.4f);
	//m_map_Meshes["Water"]->m_uTextureArray[0] = LoadTGA("particle");

	m_map_Animated["Smoke"] = MeshBuilder::GenerateAnimatedMesh("Smoke", 5, 8, 0, 39, 2.f, true);
	m_map_Animated["Smoke"]->m_Mesh->m_uTextureArray[0] = LoadTGA("Smoke");

	/*m_map_Animated["Cat"] = MeshBuilder::GenerateAnimatedMesh("Cat", 5, 8, 0, 39, 2.f, true);
	m_map_Animated["Cat"]->m_Mesh->m_uTextureArray[0] = LoadTGA("Cat");*/

	m_map_Animated["Leaf"] = MeshBuilder::GenerateAnimatedMesh("Leaf", 4, 4, 0, 15, 2.f, true);
	m_map_Animated["Leaf"]->m_Mesh->m_uTextureArray[0] = LoadTGA("Leaf");

	/*m_map_Meshes["Fish"] = MeshBuilder::GenerateQuad("TestParticle", { 1.f,1.f,1.f }, 1.1f);
	m_map_Meshes["Fish"]->m_uTextureArray[0] = LoadTGA("Fish");

	m_map_Meshes["Droplet"] = MeshBuilder::GenerateQuad("TestParticle", { 1.f,1.f,1.f }, 1.2f);
	m_map_Meshes["Droplet"]->m_uTextureArray[0] = LoadTGA("particle");

	m_map_Meshes["DropletMini"] = MeshBuilder::GenerateQuad("TestParticle", { 1.f,1.f,1.f }, 0.2f);
	m_map_Meshes["DropletMini"]->m_uTextureArray[0] = LoadTGA("particle");

	m_map_Meshes["WaterPlane"] = MeshBuilder::GenerateOBJ("cubeobj", "water");
	m_map_Meshes["WaterPlane"]->m_uTextureArray[0] = LoadTGA("water");*/

	m_map_Meshes["Tree"] = MeshBuilder::GenerateOBJ("treeShrunk");
	m_map_Meshes["Tree"]->m_uTextureArray[0] = LoadTGA("tree");
	m_map_Meshes["Tree"]->m_uTextureArray[0] = LoadTGA("moss1");

	m_map_Meshes["Crosshair"] = MeshBuilder::GenerateQuad("Crosshair", { 1.f,1.f,1.f }, 2);
	m_map_Meshes["Crosshair"]->m_uTextureArray[0] = LoadTGA("Crosshair");

	m_map_Meshes["Gaunt"] = MeshBuilder::GenerateQuad("Gaunt", { 1.f,1.f,1.f }, 1);
	m_map_Meshes["Gaunt"]->m_uTextureArray[0] = LoadTGA("Gaunt");

	m_map_Meshes["GauntSoul"] = MeshBuilder::GenerateQuad("Gaunt", { 1.f,1.f,1.f }, 1);
	m_map_Meshes["GauntSoul"]->m_uTextureArray[0] = LoadTGA("GauntSoul");

	m_map_Meshes["GauntReality"] = MeshBuilder::GenerateQuad("Gaunt", { 1.f,1.f,1.f }, 1);
	m_map_Meshes["GauntReality"]->m_uTextureArray[0] = LoadTGA("GauntReality");

	m_map_Meshes["GauntSpace"] = MeshBuilder::GenerateQuad("Gaunt", { 1.f,1.f,1.f }, 1);
	m_map_Meshes["GauntSpace"]->m_uTextureArray[0] = LoadTGA("GauntSpace");

	m_map_Meshes["GauntPower"] = MeshBuilder::GenerateQuad("Gaunt", { 1.f,1.f,1.f }, 1);
	m_map_Meshes["GauntPower"]->m_uTextureArray[0] = LoadTGA("GauntPower");

	m_map_Meshes["GauntPower"] = MeshBuilder::GenerateQuad("Gaunt", { 1.f,1.f,1.f }, 1);
	m_map_Meshes["GauntPower"]->m_uTextureArray[0] = LoadTGA("GauntPower");

	m_map_Meshes["GauntTime"] = MeshBuilder::GenerateQuad("Gaunt", { 1.f,1.f,1.f }, 1);
	m_map_Meshes["GauntTime"]->m_uTextureArray[0] = LoadTGA("gauntTime");

	m_map_Meshes["GauntMind"] = MeshBuilder::GenerateQuad("Gaunt", { 1.f,1.f,1.f }, 1);
	m_map_Meshes["GauntMind"]->m_uTextureArray[0] = LoadTGA("GauntMind");

	m_map_Meshes["GauntFist"] = MeshBuilder::GenerateQuad("Gaunt", { 1.f,1.f,1.f }, 1);
	m_map_Meshes["GauntFist"]->m_uTextureArray[0] = LoadTGA("GauntFist");
	// Gameobjects================================================================================
	GameObject* go;
	// Particle--------------------------------------------------------------------------------
	//Smoke--------------------------------------------------------------------------------
	GameObject* SmokeParticle = new GameObject;
	SmokeParticle->AddComponent(new RenderComponent(this->GetAnimation("Smoke")));
	SmokeParticle->GetComponent<RenderComponent>()->SetBillboard(true);
	SmokeParticle->AddComponent(new ParticleScript(3.0f, { 0,0.01f,0 }, { 0,0,0 }, { 0,0,0 }, { 0,0,0 }, {}));
	m_map_GO["SmokeParticle"] = SmokeParticle;
	//// Fish--------------------------------------------------------------------------------
	//GameObject* Fish = new GameObject;
	//Fish->AddComponent(new RenderComponent(this->GetMesh("Fish")));
	//Fish->GetComponent<RenderComponent>()->SetBillboard(true);
	//Fish->AddComponent(new ParticleScript(5.0f, { 0.15f,0.4f,0.0f }, { 0,0,0 }, { 0,-1.f,0 }, { -0.5,-0.5f,0 }, { 0,0,0 }));
	//m_map_GO["Fish"] = Fish;
	//// Droplet--------------------------------------------------------------------------------
	//GameObject* Droplet = new GameObject;
	//Droplet->AddComponent(new RenderComponent(this->GetMesh("Droplet")));
	//Droplet->GetComponent<RenderComponent>()->SetBillboard(true);
	//Droplet->AddComponent(new ParticleScript(5.0f, { 0.2f,0.5f,0.2f }, { 0,0,0 }, { 0,-1.f,0 }, { -0.5,-0.5f,0 }, { 1,0,1 }));
	//m_map_GO["Droplet"] = Droplet;
	//// DropletMini--------------------------------------------------------------------------------
	//GameObject* DropletMini = new GameObject;
	//DropletMini->AddComponent(new RenderComponent(this->GetMesh("DropletMini")));
	//DropletMini->GetComponent<RenderComponent>()->SetBillboard(true);
	//DropletMini->AddComponent(new ParticleScript(5.0f, { 0.3f,0.4f,0.3f }, { 0,0,0 }, { 0,-1.f,0 }, { -0.5,-0.5f,0 }, { 1,0,1 }));
	//m_map_GO["DropletMini"] = DropletMini;
	// Leaf--------------------------------------------------------------------------------
	GameObject* Leaf = new GameObject;
	m_map_GO["Leaf"] = Leaf;
	Leaf->AddComponent(new RenderComponent(this->GetAnimation("Leaf")));
	Leaf->GetComponent<RenderComponent>()->SetBillboard(true);
	Leaf->AddComponent(new ParticleScript(6.5f, { 0,-0.1f,0 }, { 0,0,0 }, { 0,-0.02f,0 }, { -0.1f,-0.1f,0 }, {}, { 0.1,0.1,0.1 }, { 1,1,1 }));
	// Leaf Spawner--------------------------------------------------------------------------------
	GameObject* LeafSpawner = new GameObject;
	LeafSpawner->AddComponent(new ParticleSpawnerScript(this->GetGameObject("Leaf"), 0.8f, { 10,2,10 }, .2f, "Default", -1.f));
	m_map_GO["LeafSpawner"] = LeafSpawner;
	// Smoke Spawner--------------------------------------------------------------------------------
	GameObject* Spawner = new GameObject;
	Spawner->AddComponent(new ParticleSpawnerScript(this->GetGameObject("SmokeParticle"), 0.2f, { .1f,.1f,.1f }, .8f, "Smoke"));
	//// Fountain Spawner--------------------------------------------------------------------------------
	//GameObject* Fountain = new GameObject;
	//Fountain->AddComponent(new ParticleSpawnerScript(this->GetGameObject("DropletMini"), 0.05f, { 0,0,0 }, .2f, "Default", 0.4f));
	//m_map_GO["Fountain"] = Fountain;
	//// Rain Spawner--------------------------------------------------------------------------------
	//GameObject* Rain = new GameObject;
	//Rain->AddComponent(new RenderComponent(this->GetMesh("Water")));
	//Rain->GetComponent<RenderComponent>()->SetBillboard(true);
	//Rain->AddComponent(new ParticleScript(4.0f, { 0,-0.7f,0 }, { 0,0,0 }, { 0,0,0 }, { 0.0f,0,0 }, {}));
	//Rain->AddComponent(new RainScript(this->GetGameObject("Fountain")));
	//m_map_GO["Rain"] = Rain;
	// Misc--------------------------------------------------------------------------------
	//Bullet--------------------------------------------------------------------------------
	GameObject* bullet = new GameObject();
	bullet->AddComponent(new RenderComponent(this->GetMesh("ball")));
	bullet->GetComponent<RenderComponent>()->SetLightEnabled(true);
	bullet->AddComponent(new BulletScript(20.f));
	ChengRigidbody* rigid = new ChengRigidbody(ChengRigidbody::BALL);
	rigid->SetMat(1, 0.5f);
	rigid->LockYAxis(true);
	bullet->AddComponent(rigid);
	bullet->AddComponent(new BallScript());
	//bullet->AddChild(Spawner);
	m_map_GO["bullet"] = bullet;
	// --------------------------------------------------------------------------------
	GameObject* wall = new GameObject;
	m_map_GO["wall"] = wall;
	wall->GetComponent<TransformComponent>()->SetRotation(-90, 0, 1, 0);
	wall->AddComponent(new RenderComponent(this->GetMesh("wall")));
	wall->AddComponent(new ChengRigidbody(ChengRigidbody::WALL, false));
	// --------------------------------------------------------------------------------
	go = new GameObject;
	m_map_GO["square"] = go;
	go->GetComponent<TransformComponent>()->SetRotation(-90, 0, 1, 0);
	go->AddComponent(new RenderComponent(this->GetMesh("square")));
	go->AddComponent(new ChengRigidbody(ChengRigidbody::SQUARE, false));
	// Score--------------------------------------------------------------------------------
	go = new GameObject;
	m_map_GO["scoreboard"] = go;
	ScoreScript* scoreScript = new ScoreScript;
	go->AddComponent(scoreScript);
	go->GetComponent<TransformComponent>()->SetPosition(50, 50, 100);
	go->AddComponent(new RenderComponent(GetMesh("Text"), "oof"));
	//Goal --------------------------------------------------------------------------------
	go = new GameObject;
	m_map_GO["goal"] = go;
	go->GetComponent<TransformComponent>()->SetRotation(-90, 0, 1, 0);
	go->AddComponent(new RenderComponent(this->GetMesh("goal")));
	go->AddComponent(new ChengRigidbody(ChengRigidbody::WALL, false));
	go->AddComponent(new GoalScript(scoreScript));
	//Pillar--------------------------------------------------------------------------------
	GameObject* pillar = new GameObject;
	m_map_GO["pillar"] = pillar;
	pillar->AddComponent(new RenderComponent(this->GetMesh("pillar")));
	pillar->AddComponent(new ChengRigidbody(ChengRigidbody::PILLAR, false));
	pillar->AddComponent(new BouncerScript(5.f, scoreScript));
	//Player Pillar--------------------------------------------------------------------------------
	go = new GameObject;
	m_map_GO["playerPillar"] = go;
	go->TRANS->SetRelativeScale({ 5, 50, 5 });
	go->AddComponent(new RenderComponent(this->GetMesh("pillar")));
	go->AddComponent(new ChengRigidbody(ChengRigidbody::PILLAR, false));
	go->AddComponent(new BouncerScript(1.f, scoreScript, true));
	// Paddle--------------------------------------------------------------------------------
	go = new GameObject;
	m_map_GO["paddle"] = go;
	go->AddComponent(new RenderComponent(this->GetMesh("paddle")));
	go->GetComponent<RenderComponent>()->SetColor({ 0,0,1 });
	go->AddComponent(new ChengRigidbody(ChengRigidbody::PADDLE, false));
	go->AddComponent(new PaddleScript(true));
	go->GetComponent<TransformComponent>()->SetScale(5, 100, 35);
	// PaddleRight--------------------------------------------------------------------------------
	go = new GameObject;
	m_map_GO["paddleRight"] = go;
	go->AddComponent(new RenderComponent(this->GetMesh("paddle")));
	go->GetComponent<RenderComponent>()->SetColor({ 0,0,1 });
	go->AddComponent(new ChengRigidbody(ChengRigidbody::PADDLE, false));
	go->AddComponent(new PaddleScript(false));
	go->GetComponent<TransformComponent>()->SetScale(5, 100, 35);
	// Fan--------------------------------------------------------------------------------
	go = new GameObject;
	m_map_GO["fanBlade"] = go;
	go->AddComponent(new RenderComponent(this->GetMesh("paddle")));
	go->GetComponent<RenderComponent>()->SetColor({ 1,0,1 });
	ChengRigidbody* rb = new ChengRigidbody(ChengRigidbody::PADDLE, false);
	rb->SetAVel({ 0, 120, 0 });
	go->AddComponent(rb);
	go->GetComponent<TransformComponent>()->SetScale(2, 100, 20);
	// World================================================================================
	// tree--------------------------------------------------------------------------------
	go = new GameObject;
	m_map_GO["Tree"] = go;
	go->AddComponent(new RenderComponent(this->GetMesh("Tree")));
	go->AddComponent(new ChengRigidbody(ChengRigidbody::PILLAR, false));
	go->TRANS->SetScale(5, 10, 5);
	// Shaders================================================================================
	m_map_Shaders["Default"] = LoadShaders("Flare", "Flare");
	m_map_Shaders["Water"] = LoadShaders("water", "water");
	m_map_Shaders["GPass"] = LoadShaders("GPass", "GPass");
	m_map_Shaders["Smoke"] = LoadShaders("Smoke", "Smoke");
	m_map_Shaders["Underwater"] = LoadShaders("Underwater", "Underwater");
	//--------------------------------------------------------------------------------

	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

	CHENG_LOG("Time to load container: ", std::to_string(elapsed_secs));
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
	for (it3 = m_map_GO.begin(); it3 != m_map_GO.end(); it3++)
	{
		// it->first == key
		// it->second == value
		delete it3->second;
	}
	m_map_GO.clear();
	for (auto const& x : m_map_HeightMaps)
	{
		delete x.second;
	}
	m_map_HeightMaps.clear();
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
	{
		DEFAULT_LOG("ERROR: GameObject not found of name: " + name);
		return nullptr;
	}
	return go->Clone();
}
unsigned DataContainer::GetShader(std::string key)
{
	if (m_map_Shaders.count(key) <= 0)
		DEFAULT_LOG("ERROR: Shader not found of name: " + key);
	unsigned shader = m_map_Shaders[key];
	return shader;
}
HeightMapData* DataContainer::GetHeightMap(std::string key)
{
	if (m_map_HeightMaps.count(key) <= 0)
		DEFAULT_LOG("ERROR: Heightmap not found of name: " + key);
	return m_map_HeightMaps[key];
}
Mesh* DataContainer::GenerateTerrain(std::string key, std::string path, Vector3 vScale)
{
	_heightmap* heightMap = new _heightmap;
	Mesh* mesh = MeshBuilder::GenerateTerrain(key, path, *heightMap, vScale);
	m_map_HeightMaps[key] = new HeightMapData(mesh, heightMap, vScale);
	return mesh;
}