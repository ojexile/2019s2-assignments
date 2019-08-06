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
#include "HoleScript.h"
#include "MeshController.h"
#include "GauntletScript.h"
#include "FPSScript.h"
#include "GunScript.h"
#include "Constrain.h"
#include "EnemyAIScript.h"
#include <time.h>
DataContainer::DataContainer()
{
	clock_t begin = clock();
	/// Meshes================================================================================
	m_map_Meshes["Text"] = MeshBuilder::GenerateText("text", 16, 16);
	m_map_Meshes["Text"]->m_uTextureArray[0] = LoadTGA("calibri");

	m_map_Meshes["ground"] = MeshBuilder::GenerateQuad("ground", { 1.f,1.f,1.f }, 500);

	m_map_Meshes["ball"] = MeshBuilder::GenerateOBJ("ball");
	m_map_Meshes["ball"]->m_uTextureArray[0] = LoadTGA("ball");

	m_map_Meshes["sun"] = MeshBuilder::GenerateSphere("ball", Color(1, 1, 1), 10, 10, 1.f);

	m_map_Meshes["pillar"] = MeshBuilder::GenerateOBJ("cylinder");

	m_map_Meshes["paddle"] = MeshBuilder::GenerateOBJ("paddle");

	m_map_Meshes["Colt"] = MeshBuilder::GenerateOBJ("colt");
	m_map_Meshes["Colt"]->m_uTextureArray[0] = LoadTGA("Colt");

	m_map_Meshes["AmmoBox"] = MeshBuilder::GenerateOBJ("AmmoBox");
	m_map_Meshes["AmmoBox"]->m_uTextureArray[0] = LoadTGA("AmmoBox");

	m_map_Meshes["wall"] = MeshBuilder::GenerateCube("wall", Color((float)0.2, (float)0.2, (float)0.2), 1.f);

	m_map_Meshes["square"] = MeshBuilder::GenerateCube("wall", Color((float)0.5, (float)0.5, (float)0.2), 1.f);

	m_map_Meshes["goal"] = MeshBuilder::GenerateCube("wall", Color((float)0.8, (float)0.2, (float)0.2), 1.f);

	m_map_Meshes["Quad"] = MeshBuilder::GenerateQuadLeftCentered(Color(1.f, 1.f, 1.f), 1.f);

	m_map_Meshes["SkyPlane"] = MeshBuilder::GenerateSkyPlane("SkyPlane", { 0,0,1 }, 24, 6, 400, 6, 6);
	m_map_Meshes["SkyPlane"]->m_uTextureArray[0] = LoadTGA("sky");

	m_map_Meshes["Gun"] = MeshBuilder::GenerateQuad("QUAD", { 1,1,1 }, 1.f);
	m_map_Meshes["Gun"]->m_uTextureArray[0] = LoadTGA("PLAYER_PISTOL");

	m_map_Meshes["Assualt"] = MeshBuilder::GenerateQuad("QUAD", { 1,1,1 }, 1.f);
	m_map_Meshes["Assualt"]->m_uTextureArray[0] = LoadTGA("PLAYER_ASSAULT");

	m_map_Meshes["Particle"] = MeshBuilder::GenerateQuad("Particle", { 1.f,1.f,1.f }, 1);
	m_map_Meshes["Particle"]->m_uTextureArray[0] = LoadTGA("Particle");

	m_map_Animated["Smoke"] = MeshBuilder::GenerateAnimatedMesh("Smoke", 5, 8, 0, 39, 2.f, false);
	m_map_Animated["Smoke"]->m_Mesh->m_uTextureArray[0] = LoadTGA("Smoke");

	/*m_map_Animated["Cat"] = MeshBuilder::GenerateAnimatedMesh("Cat", 5, 8, 0, 39, 2.f, true);
	m_map_Animated["Cat"]->m_Mesh->m_uTextureArray[0] = LoadTGA("Cat");*/

	m_map_Animated["Leaf"] = MeshBuilder::GenerateAnimatedMesh("Leaf", 4, 4, 0, 15, 2.f, true);
	m_map_Animated["Leaf"]->m_Mesh->m_uTextureArray[0] = LoadTGA("Leaf2");

	m_map_Meshes["Droplet"] = MeshBuilder::GenerateQuad("Droplet", { 1.f,1.f,1.f }, 1.2f);
	m_map_Meshes["Droplet"]->m_uTextureArray[0] = LoadTGA("Droplet2");

	m_map_Meshes["WaterPlane"] = MeshBuilder::GenerateOBJ("water");
	m_map_Meshes["WaterPlane"]->m_uTextureArray[0] = LoadTGA("water");

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

	m_map_Meshes["GauntTime"] = MeshBuilder::GenerateQuad("Gaunt", { 1.f,1.f,1.f }, 1);
	m_map_Meshes["GauntTime"]->m_uTextureArray[0] = LoadTGA("gauntTime");

	m_map_Meshes["GauntMind"] = MeshBuilder::GenerateQuad("Gaunt", { 1.f,1.f,1.f }, 1);
	m_map_Meshes["GauntMind"]->m_uTextureArray[0] = LoadTGA("GauntMind");

	m_map_Meshes["GauntFist"] = MeshBuilder::GenerateQuad("Gaunt", { 1.f,1.f,1.f }, 1);
	m_map_Meshes["GauntFist"]->m_uTextureArray[0] = LoadTGA("GauntFist");

	m_map_Meshes["GauntSnap"] = MeshBuilder::GenerateQuad("Gaunt", { 1.f,1.f,1.f }, 1);
	m_map_Meshes["GauntSnap"]->m_uTextureArray[0] = LoadTGA("GauntSnap");

	/// Terrain================================================================================
	// Plains--------------------------------------------------------------------------------
	Mesh* mesh = GenerateTerrain("TerrainPlains", "heightmapPlains", { 200,60,200 }, { 99,0,99 });
	mesh->m_uTextureArray[0] = LoadTGA("dirt");
	mesh->m_uTextureArray[1] = LoadTGA("grassdirt");
	mesh->m_uTextureArray[2] = LoadTGA("grassdirt");
	// Terrace---------------------------------------------------------------------------------
	mesh = GenerateTerrainTerrace("TerrainTerrace", "heightmapTerrace", { 200,40,200 }, { -99,0,-99 });
	mesh->m_uTextureArray[0] = LoadTGA("moss1");
	mesh->m_uTextureArray[1] = LoadTGA("grass");
	// Snow--------------------------------------------------------------------------------
	mesh = GenerateTerrain("TerrainSnow", "heightmapSnow", { 200,190,200 }, { 99,0,-99 });
	mesh->m_uTextureArray[0] = LoadTGA("snow");
	mesh->m_uTextureArray[1] = LoadTGA("stone");
	// Desert--------------------------------------------------------------------------------
	mesh = GenerateTerrain("TerrainDesert", "heightmapDesert", { 200,100,200 }, { -99,0,99 });
	mesh->m_uTextureArray[0] = LoadTGA("sand");
	mesh->m_uTextureArray[1] = LoadTGA("sandhill");
	// Flat--------------------------------------------------------------------------------
	mesh = GenerateTerrain("TerrainFlat", "heightmapFlat", { 1000,40,1000 }, { 0,0,0 });
	mesh->m_uTextureArray[0] = LoadTGA("moss1");
	mesh->m_uTextureArray[1] = LoadTGA("sky");
	/// Gameobjects================================================================================
	GameObject* go;
	/// Particles--------------------------------------------------------------------------------
	//Smoke--------------------------------------------------------------------------------
	GameObject* SmokeParticle = new GameObject;
	m_map_GO["SmokeParticle"] = SmokeParticle;
	SmokeParticle->AddComponent(new RenderComponent(this->GetAnimation("Smoke")));
	SmokeParticle->GetComponent<RenderComponent>()->SetBillboard(true);
	SmokeParticle->AddComponent(new ParticleScript(3.0f, { 0,0.01f,0 }, { 0,0,0 }, { 0,0,0 }, { 0,0,0 }, {}));
	// Gaunt Charge Particle--------------------------------------------------------------------------------
	go = new GameObject;
	m_map_GO["Particle"] = go;
	go->AddComponent(new RenderComponent(this->GetMesh("Particle")));
	go->TRANS->SetScale(10, 10, 1);
	go->RENDER->SetLightEnabled(false);
	go->RENDER->SetColor({ 0,1,1 });
	ParticleScript* ps1 = new ParticleScript(1.5f, { 1.f,1.f,0 }, { 0,0,0 }, { 0,0,0 }, { -6.f,-6.f,0 }, { 1,1,0 }, { 0,0,0 }, { 0,0,0 });
	go->AddComponent(ps1);
	// Leaf--------------------------------------------------------------------------------
	GameObject* Leaf = new GameObject;
	m_map_GO["Leaf"] = Leaf;
	Leaf->AddComponent(new RenderComponent(this->GetAnimation("Leaf")));
	Leaf->GetComponent<RenderComponent>()->SetBillboard(true);
	float ampl = 0.1f;
	float freq = 0.8f;
	ParticleScript* ps = new ParticleScript(12.5f, { 0,-0.03f,0 }, { 0,0,0 }, { 0,-0.02f,0 }, { -0.01f,-0.01f,0 }, {}, { ampl,0,0 }, { freq,0,0 });
	//ps->SetCos({ 0,0,ampl }, { 0,0,freq });
	ps->SetRot({ 0,0,50 });
	Leaf->AddComponent(ps);
	// Leaf Spawner--------------------------------------------------------------------------------
	GameObject* LeafSpawner = new GameObject;
	m_map_GO["LeafSpawner"] = LeafSpawner;
	LeafSpawner->AddComponent(new ParticleSpawnerScript(GetGameObject("Leaf"), 1.5f, { 10,5,10 }, 1.f, "Default", -1.f));
	// Smoke Spawner--------------------------------------------------------------------------------
	/*m_map_GO["SmokeSpawner"] = LeafSpawner;
	GameObject* Spawner = new GameObject;
	Spawner->AddComponent(new ParticleSpawnerScript(this->GetGameObject("SmokeParticle"), 0.8f, { .1f,.1f,.1f }, .8f, "Smoke"));*/
	/// Rain================================================================================
	// DropletMini--------------------------------------------------------------------------------
	GameObject* DropletMini = new GameObject;
	DropletMini->AddComponent(new RenderComponent(this->GetMesh("Droplet")));
	DropletMini->TRANS->SetScale(0.4f);
	DropletMini->RENDER->SetLightEnabled(false);
	DropletMini->GetComponent<RenderComponent>()->SetBillboard(true);
	DropletMini->AddComponent(new ParticleScript(1.0f, { 0.3f,0.4f,0.3f }, { 0,0,0 }, { 0,-1.f,0 }, { -0.5,-0.5f,0 }, { 1,0,1 }));
	m_map_GO["DropletMini"] = DropletMini;
	// Fountain Spawner--------------------------------------------------------------------------------
	GameObject* Fountain = new GameObject;
	Fountain->AddComponent(new ParticleSpawnerScript(this->GetGameObject("DropletMini"), 0.1f, { 0,0,0 }, .2f, "Default", 0.4f));
	m_map_GO["Fountain"] = Fountain;
	// Rain--------------------------------------------------------------------------------
	GameObject* Rain = new GameObject;
	Rain->TRANS->SetScale(0.2f, 1, 0.2f);
	Rain->AddComponent(new RenderComponent(this->GetMesh("Droplet")));
	Rain->GetComponent<RenderComponent>()->SetBillboard(true);
	Rain->AddComponent(new ParticleScript(5.0f, { 0,-1.7f,0 }, { 0,0,0 }, { 0,0,0 }, { 0.0f,0,0 }, {}));
	Rain->AddComponent(new RainScript(Fountain));
	Rain->RENDER->SetLightEnabled(false);
	m_map_GO["Rain"] = Rain;
	// Rain Spawner--------------------------------------------------------------------------------
	GameObject* RainSpawner = new GameObject;
	RainSpawner->TRANS->SetPosition(0, 100, 0);
	RainSpawner->AddComponent(new ParticleSpawnerScript(this->GetGameObject("Rain"), 0.3f, { 100,0,100 }, .2f, "Default", -1.f));
	m_map_GO["RainSpawner"] = RainSpawner;
	// ================================================================================
	/// Snow================================================================================
	// Rain--------------------------------------------------------------------------------
	GameObject* Snow = new GameObject;
	m_map_GO["Snow"] = Snow;
	Snow->AddComponent(new RenderComponent(this->GetMesh("Particle")));
	Snow->GetComponent<RenderComponent>()->SetBillboard(true);
	ParticleScript* snowps = new ParticleScript(25.0f, { 0,-.2f,0 }, { 0,0,0 }, { 0,0.001f,0 }, { -0.04f,-0.04f,0 }, {}, { 0.1f,0,0 }, { 1.1f,0,0 });
	snowps->SetCos({ 0,0, 0.1f }, { 0, 0,1.1f });
	Snow->AddComponent(snowps);
	Snow->RENDER->SetLightEnabled(false);
	// Rain Spawner--------------------------------------------------------------------------------
	GameObject* SnowSpawner = new GameObject;
	m_map_GO["SnowSpawner"] = SnowSpawner;
	SnowSpawner->AddComponent(new ParticleSpawnerScript(this->GetGameObject("Snow"), 0.2f, { 100,0,100 }, 0.8f, "Default", -1.f));
	// ================================================================================
	///--------------------------------------------------------------------------------
	//Bullet--------------------------------------------------------------------------------
	GameObject* bullet = new GameObject();
	m_map_GO["bullet"] = bullet;
	bullet->AddComponent(new RenderComponent(this->GetMesh("ball")));
	bullet->GetComponent<RenderComponent>()->SetLightEnabled(true);
	bullet->AddComponent(new BulletScript(30.f, 1));
	ChengRigidbody* rigid = new ChengRigidbody(ChengRigidbody::BALL);
	rigid->SetMat(1, 0.5f);
	rigid->SetGravity({ 0,0.5f,0 });
	bullet->AddComponent(rigid);
	bullet->AddComponent(new BallScript());
	// Assualt Bullet--------------------------------------------------------------------------------
	go = new GameObject();
	m_map_GO["AssualtBullet"] = go;
	go->TRANS->SetScale(0.1f);
	go->AddComponent(new RenderComponent(this->GetMesh("ball")));
	go->GetComponent<RenderComponent>()->SetLightEnabled(true);
	rigid = new ChengRigidbody(ChengRigidbody::BALL);
	rigid->SetMat(1, 0.5f);
	rigid->SetGravity({ 0,0.5f,0 });
	go->AddComponent(new BulletScript(3.f, 10));
	go->AddComponent(rigid);
	// Assualt Bullet--------------------------------------------------------------------------------
	go = new GameObject();
	m_map_GO["ColtBullet"] = go;
	go->TRANS->SetScale(0.4f);
	go->AddComponent(new RenderComponent(this->GetMesh("ball")));
	go->GetComponent<RenderComponent>()->SetLightEnabled(true);
	rigid = new ChengRigidbody(ChengRigidbody::BALL);
	rigid->SetMat(1, 0.5f);
	rigid->SetGravity({ 0,0.5f,0 });
	go->AddComponent(new BulletScript(3.f, 70));
	go->AddComponent(rigid);
	// --------------------------------------------------------------------------------
	GameObject* wall = new GameObject;
	m_map_GO["wall"] = wall;
	wall->GetComponent<TransformComponent>()->SetRotation(-90, 0, 1, 0);
	wall->AddComponent(new RenderComponent(this->GetMesh("wall")));
	wall->AddComponent(new ChengRigidbody(ChengRigidbody::WALL, false));
	// Square--------------------------------------------------------------------------------
	go = new GameObject;
	m_map_GO["square"] = go;
	go->GetComponent<TransformComponent>()->SetRotation(-90, 0, 1, 0);
	go->AddComponent(new RenderComponent(this->GetMesh("square")));
	go->AddComponent(new ChengRigidbody(ChengRigidbody::SQUARE, false));
	//Square Hole--------------------------------------------------------------------------------
	go = new GameObject;
	m_map_GO["squareHole"] = go;
	go->TRANS->SetScale(7, 100, 7);
	go->AddComponent(new RenderComponent(this->GetMesh("square")));
	go->RENDER->SetColor({ 0,0,0 });
	go->AddComponent(new ChengRigidbody(ChengRigidbody::SQUARE, false));
	go->AddComponent(new HoleScript);
	/// Gameplay================================================================================
	//Gauntlet--------------------------------------------------------------------------------
	GameObject* Gaunt = new GameObject;
	m_map_GO["Gauntlet"] = Gaunt;
	Gaunt->TRANS->SetPosition(250, 1080 - 800, 5);
	Gaunt->TRANS->SetScale(800.f, 800.f, 1.f);
	Gaunt->AddComponent(new RenderComponent(GetMesh("Gaunt")));
	Gaunt->RENDER->SetLightEnabled(false);
	MeshController<Mesh>* meshController = new MeshController<Mesh>;
	meshController->AddMesh("Gaunt", GetMesh("Gaunt"));
	meshController->AddMesh("GauntSoul", GetMesh("GauntSoul"));
	meshController->AddMesh("GauntReality", GetMesh("GauntReality"));
	meshController->AddMesh("GauntSpace", GetMesh("GauntSpace"));
	meshController->AddMesh("GauntPower", GetMesh("GauntPower"));
	meshController->AddMesh("GauntTime", GetMesh("GauntTime"));
	meshController->AddMesh("GauntMind", GetMesh("GauntMind"));
	meshController->AddMesh("GauntFist", GetMesh("GauntFist"));
	meshController->AddMesh("GauntSnap", GetMesh("GauntSnap"));
	Gaunt->AddComponent(meshController);
	GameObject* go2 = new GameObject;
	m_map_GO["Text"] = go2;
	go2->AddComponent(new RenderComponent(GetMesh("Text"), ""));
	go2->TRANS->SetPosition(1200, 960, 25);
	go2->RENDER->SetColor({ 1,1,1 });
	/// World================================================================================
	// tree--------------------------------------------------------------------------------
	go = new GameObject;
	m_map_GO["Tree"] = go;
	go->AddComponent(new RenderComponent(this->GetMesh("Tree")));
	go->AddComponent(new ChengRigidbody(ChengRigidbody::PILLAR, false));
	go->TRANS->SetScale(15, 100, 15);
	/// Pinball================================================================================
	// Score--------------------------------------------------------------------------------
	go = new GameObject;
	m_map_GO["scoreboard"] = go;
	ScoreScript* scoreScript = new ScoreScript;
	go->AddComponent(scoreScript);
	go->TRANS->SetPosition(50, 50, 100);
	go->AddComponent(new RenderComponent(GetMesh("Text"), "oof"));
	go->RENDER->SetColor({ 1,1,1 });
	//Pillar--------------------------------------------------------------------------------
	GameObject* pillar = new GameObject;
	m_map_GO["pillar"] = pillar;
	pillar->AddComponent(new RenderComponent(this->GetMesh("pillar")));
	pillar->AddComponent(new ChengRigidbody(ChengRigidbody::PILLAR, false));
	pillar->AddComponent(new BouncerScript(5.f, scoreScript));
	//Pillar Hole--------------------------------------------------------------------------------
	go = new GameObject;
	m_map_GO["pillarHole"] = go;
	go->AddComponent(new RenderComponent(this->GetMesh("pillar")));
	go->RENDER->SetColor({ 0,0,0 });
	go->TRANS->SetScale(7, 100, 7);
	go->AddComponent(new ChengRigidbody(ChengRigidbody::PILLAR, false));
	go->AddComponent(new HoleScript);
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
	go->GetComponent<TransformComponent>()->SetScale(5, 60, 35);
	// PaddleRight--------------------------------------------------------------------------------
	go = new GameObject;
	m_map_GO["paddleRight"] = go;
	go->AddComponent(new RenderComponent(this->GetMesh("paddle")));
	go->GetComponent<RenderComponent>()->SetColor({ 0,0,1 });
	go->AddComponent(new ChengRigidbody(ChengRigidbody::PADDLE, false));
	go->AddComponent(new PaddleScript(false));
	go->GetComponent<TransformComponent>()->SetScale(5, 60, 35);
	// Fan--------------------------------------------------------------------------------
	go = new GameObject;
	m_map_GO["fanBlade"] = go;
	go->AddComponent(new RenderComponent(this->GetMesh("paddle")));
	go->GetComponent<RenderComponent>()->SetColor({ 1,0,1 });
	ChengRigidbody* rb = new ChengRigidbody(ChengRigidbody::PADDLE, false);
	rb->SetAVel({ 0, 120, 0 });
	go->AddComponent(rb);
	go->GetComponent<TransformComponent>()->SetScale(2, 100, 20);
	//Goal --------------------------------------------------------------------------------
	go = new GameObject;
	m_map_GO["goal"] = go;
	go->GetComponent<TransformComponent>()->SetRotation(-90, 0, 1, 0);
	go->AddComponent(new RenderComponent(this->GetMesh("goal")));
	go->AddComponent(new ChengRigidbody(ChengRigidbody::WALL, false));
	go->AddComponent(new GoalScript(scoreScript));
	/// misc================================================================================
	go = new GameObject;
	m_map_GO["FPS"] = go;
	go->AddComponent(new FPSScript);
	go->TRANS->SetPosition(50, 10, 25);
	go->AddComponent(new RenderComponent(GetMesh("Text"), "0"));
	go->RENDER->SetColor({ 0.7f,1.7f,0.7f });
	/// Gun--------------------------------------------------------------------------------
	go = new GameObject;
	m_map_GO["BallGun"] = go;
	go->AddComponent(new RenderComponent(this->GetMesh("Gun")));
	go->RENDER->SetLightEnabled(false);
	go->RENDER->SetBillboard(true);
	go->AddComponent(new GunScript(m_map_GO["bullet"], 0.1f, GunScript::CHARGE, m_map_GO["SmokeParticle"], 150, 3, 3));
	go->GetComponent<GunScript>()->SetRecoil(3);
	go->TRANS->SetScale(5);
	/// Assualt--------------------------------------------------------------------------------
	go = new GameObject;
	m_map_GO["Assualt"] = go;
	go->TRANS->SetScale(4);
	go->AddComponent(new RenderComponent(this->GetMesh("Assualt")));
	go->RENDER->SetLightEnabled(false);
	go->RENDER->SetBillboard(true);
	go->AddComponent(new GunScript(m_map_GO["AssualtBullet"], 0.1f, GunScript::FULL_AUTO, m_map_GO["SmokeParticle"], 150, 25, 3));
	go->GetComponent<GunScript>()->SetRecoil(1);
	/// Colt--------------------------------------------------------------------------------
	go = new GameObject;
	m_map_GO["Colt"] = go;
	go->AddComponent(new RenderComponent(this->GetMesh("Colt")));
	go->RENDER->SetLightEnabled(false);
	//	go->RENDER->SetBillboard(true);
	go->AddComponent(new GunScript(m_map_GO["AssualtBullet"], 0.4f, GunScript::SEMI_AUTO, m_map_GO["SmokeParticle"], 200, 8, 4));
	go->GetComponent<GunScript>()->SetRecoil(5);
	go->TRANS->SetScale(5);
	go->AddComponent(new ChengRigidbody(ChengRigidbody::BALL, false));
	/// Enemy--------------------------------------------------------------------------------
	go = new GameObject;
	m_map_GO["Enemy"] = go;
	go->AddComponent(new RenderComponent(this->GetMesh("pillar")));
	go->TRANS->SetScale(10, 25, 10);
	go->AddComponent(new ChengRigidbody(ChengRigidbody::PILLAR));
	go->AddComponent(new Constrain(GetHeightMap("TerrainDesert"), Constrain::FIXED));
	/// Shaders================================================================================
	m_map_Shaders["Default"] = LoadShaders("Flare", "Flare");
	m_map_Shaders["Water"] = LoadShaders("water", "water");
	m_map_Shaders["GPass"] = LoadShaders("GPass", "GPass");
	m_map_Shaders["Smoke"] = LoadShaders("Smoke", "Smoke");
	m_map_Shaders["HeatWave"] = LoadShaders("HeatWave", "HeatWave");
	m_map_Shaders["Underwater"] = LoadShaders("Underwater", "Underwater");
	m_map_Shaders["Snow"] = LoadShaders("Flare", "Snow");
	//================================================================================
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
	return new AnimatedMesh(*mesh);
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
Mesh* DataContainer::GenerateTerrain(std::string key, std::string path, Vector3 vScale, Vector3 vPos)
{
	_heightmap* heightMap = new _heightmap;
	Mesh* mesh = MeshBuilder::GenerateTerrain(key, path, *heightMap, vScale);
	m_map_HeightMaps[key] = new HeightMapData(mesh, heightMap, vScale, vPos);
	return mesh;
}
Mesh* DataContainer::GenerateTerrainTerrace(std::string key, std::string path, Vector3 vScale, Vector3 vPos)
{
	_heightmap* heightMap = new _heightmap;
	Mesh* mesh = MeshBuilder::GenerateTerrainTerrace(key, path, *heightMap, vScale);
	m_map_HeightMaps[key] = new HeightMapData(mesh, heightMap, vScale, vPos);
	return mesh;
}