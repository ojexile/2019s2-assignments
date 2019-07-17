#include "DataContainer.h"
#include "ChengRigidbody.h"
#include "BallScript.h"
#include "BulletScript.h"
#include "ParticleScript.h"
#include "ParticleSpawnerScript.h"
#include "RainScript.h"
#include "GoalScript.h"
#include "BouncerScript.h"

#include <time.h>
DataContainer::DataContainer()
{
	clock_t begin = clock();
	// Meshes================================================================================
	m_map_Meshes["Text"] = MeshBuilder::GenerateText("text", 16, 16);
	m_map_Meshes["Text"]->m_uTextureArray[0] = LoadTGA("calibri");

	m_map_Meshes["ground"] = MeshBuilder::GenerateQuad("ground", { 1.f,1.f,1.f }, 500);
	m_map_Meshes["ball"] = MeshBuilder::GenerateSphere("ball", Color(1, 0, 0), 10, 10, 1.f);
	//m_map_Meshes["ball2"] = MeshBuilder::GenerateSphere("ball", Color(0, 0, 1), 10, 10, 1.f);
	//m_map_Meshes["ball3"] = MeshBuilder::GenerateSphere("ball", Color(0, 1, 0), 10, 10, 1.f);

	m_map_Meshes["pillar"] = MeshBuilder::GenerateOBJ("cylinder");
	m_map_Meshes["wall"] = MeshBuilder::GenerateCube("wall", Color((float)0.2, (float)0.2, (float)0.2), 1.f);
	m_map_Meshes["goal"] = MeshBuilder::GenerateCube("wall", Color((float)0.8, (float)0.2, (float)0.2), 1.f);

	m_map_Meshes["SkyPlane"] = MeshBuilder::GenerateSkyPlane("SkyPlane", { 0,0,1 }, 24, 52, 1000, 6, 6);
	m_map_Meshes["SkyPlane"]->m_uTextureArray[0] = LoadTGA("sky");

	m_map_Meshes["Gun"] = MeshBuilder::GenerateQuad("QUAD", { 1,1,1 }, 1000.f);
	m_map_Meshes["Gun"]->m_uTextureArray[0] = LoadTGA("PLAYER_PISTOL");

	//m_map_Meshes["Water"] = MeshBuilder::GenerateQuad("TestParticle", { 1.f,1.f,1.f }, 0.4f);
	//m_map_Meshes["Water"]->m_uTextureArray[0] = LoadTGA("particle");

	m_map_Animated["Smoke"] = MeshBuilder::GenerateAnimatedMesh("Smoke", 5, 8, 0, 39, 2.f, false);
	m_map_Animated["Smoke"]->m_Mesh->m_uTextureArray[0] = LoadTGA("Smoke2");

	/*m_map_Animated["Leaf"] = MeshBuilder::GenerateAnimatedMesh("Leaf", 4, 4, 0, 15, 2.f, true);
	m_map_Animated["Leaf"]->m_Mesh->m_uTextureArray[0] = LoadTGA("Leaf");

	m_map_Meshes["Fish"] = MeshBuilder::GenerateQuad("TestParticle", { 1.f,1.f,1.f }, 1.1f);
	m_map_Meshes["Fish"]->m_uTextureArray[0] = LoadTGA("Fish");

	m_map_Meshes["Droplet"] = MeshBuilder::GenerateQuad("TestParticle", { 1.f,1.f,1.f }, 1.2f);
	m_map_Meshes["Droplet"]->m_uTextureArray[0] = LoadTGA("particle");

	m_map_Meshes["DropletMini"] = MeshBuilder::GenerateQuad("TestParticle", { 1.f,1.f,1.f }, 0.2f);
	m_map_Meshes["DropletMini"]->m_uTextureArray[0] = LoadTGA("particle");

	m_map_Meshes["WaterPlane"] = MeshBuilder::GenerateOBJ("cubeobj", "water");
	m_map_Meshes["WaterPlane"]->m_uTextureArray[0] = LoadTGA("water");

	m_map_Meshes["Tree"] = MeshBuilder::GenerateOBJ("tree", "tree");
	m_map_Meshes["Tree"]->m_uTextureArray[0] = LoadTGA("tree");
	m_map_Meshes["Tree"]->m_uTextureArray[0] = LoadTGA("moss1");*/

	m_map_Meshes["Crosshair"] = MeshBuilder::GenerateQuad("Crosshair", { 1.f,1.f,1.f }, 2);
	m_map_Meshes["Crosshair"]->m_uTextureArray[0] = LoadTGA("Crosshair");

	m_map_Meshes["Gaunt"] = MeshBuilder::GenerateQuad("Gauntlet", { 1.f,1.f,1.f }, 1);
	m_map_Meshes["Gaunt"]->m_uTextureArray[0] = LoadTGA("Gauntlet");
	// Gameobjects================================================================================
	GameObject* go;
	// Particle--------------------------------------------------------------------------------
	//Smoke--------------------------------------------------------------------------------
	GameObject* SmokeParticle = new GameObject;
	SmokeParticle->GetComponent<TransformComponent>()->SetScale(5, 5, 5);
	SmokeParticle->AddComponent(new RenderComponent(this->GetAnimation("Smoke")));
	SmokeParticle->GetComponent<RenderComponent>()->SetBillboard(true);
	SmokeParticle->AddComponent(new ParticleScript(0.3f, { 0,0.01f,0 }, { 0,0,0 }, { 0,0,0 }, { 0,0,0 }, {}));
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
	//// Leaf--------------------------------------------------------------------------------
	//GameObject* Leaf = new GameObject;
	//Leaf->AddComponent(new RenderComponent(this->GetAnimation("Leaf")));
	//Leaf->GetComponent<RenderComponent>()->SetBillboard(true);
	//Leaf->AddComponent(new ParticleScript(6.5f, { 0,-0.2f,0 }, { 2,0,0 }, { 0,0.01f,0 }, { -0.01f,-0.01f,0 }, {}));
	//m_map_GO["Leaf"] = Leaf;
	// Smoke Spawner--------------------------------------------------------------------------------
	GameObject* Spawner = new GameObject;
	Spawner->AddComponent(new ParticleSpawnerScript(this->GetGameObject("SmokeParticle"), 0.002f, { .1f,.1f,.1f }, .8f, "Smoke"));
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
	rigid->LockYAxis(true);
	bullet->AddComponent(rigid);
	bullet->AddComponent(new BallScript());
	bullet->AddChild(Spawner);
	m_map_GO["bullet"] = bullet;
	// --------------------------------------------------------------------------------
	GameObject* wall = new GameObject;
	m_map_GO["wall"] = wall;
	wall->GetComponent<TransformComponent>()->SetRotation(-90, 0, 1, 0);
	wall->AddComponent(new RenderComponent(this->GetMesh("wall")));
	wall->AddComponent(new ChengRigidbody(ChengRigidbody::WALL, false));
	//Goal --------------------------------------------------------------------------------
	go = new GameObject;
	m_map_GO["goal"] = go;
	go->GetComponent<TransformComponent>()->SetRotation(-90, 0, 1, 0);
	go->AddComponent(new RenderComponent(this->GetMesh("goal")));
	go->AddComponent(new ChengRigidbody(ChengRigidbody::WALL, false));
	go->AddComponent(new GoalScript);
	// Score--------------------------------------------------------------------------------
	go = new GameObject;
	m_map_GO["scoreboard"] = go;
	ScoreScript* scoreScript = new ScoreScript;
	go->AddComponent(scoreScript);
	//Pillar--------------------------------------------------------------------------------
	GameObject* pillar = new GameObject;
	m_map_GO["pillar"] = pillar;
	pillar->AddComponent(new RenderComponent(this->GetMesh("pillar")));
	pillar->AddComponent(new ChengRigidbody(ChengRigidbody::PILLAR, false));
	pillar->AddComponent(new BouncerScript(1.f, scoreScript));
	//--------------------------------------------------------------------------------
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