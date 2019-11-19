#ifndef SCENE_BASE_H
#define SCENE_BASE_H

#include "Scene.h"
#include "Mtx44.h"
#include "Camera.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Light.h"
#include "GameObject.h"
#include <vector>

class SceneBase : public Scene
{
	enum UNIFORM_TYPE
	{
		U_MVP = 0,
		U_MODELVIEW,
		U_MODELVIEW_INVERSE_TRANSPOSE,
		U_MATERIAL_AMBIENT,
		U_MATERIAL_DIFFUSE,
		U_MATERIAL_SPECULAR,
		U_MATERIAL_SHININESS,
		U_LIGHTENABLED,
		U_NUMLIGHTS,
		U_LIGHT0_TYPE,
		U_LIGHT0_POSITION,
		U_LIGHT0_COLOR,
		U_LIGHT0_POWER,
		U_LIGHT0_KC,
		U_LIGHT0_KL,
		U_LIGHT0_KQ,
		U_LIGHT0_SPOTDIRECTION,
		U_LIGHT0_COSCUTOFF,
		U_LIGHT0_COSINNER,
		U_LIGHT0_EXPONENT,
		U_COLOR_TEXTURE_ENABLED,
		U_COLOR_TEXTURE,
		U_TEXT_ENABLED,
		U_TEXT_COLOR,
		U_TOTAL,
	};
public:
	enum GEOMETRY_TYPE
	{
		GEO_AXES,
		GEO_TEXT,
		GEO_BALL,
		GEO_CUBE,
		GEO_BG,
		GEO_TICTACTOE,
		GEO_CROSS,
		GEO_CIRCLE,

		GEO_FISH_TOOFULL,
		GEO_FISH_DEAD,
		GEO_FISH_FULL,
		GEO_FISH_HUNGRY,
		GEO_SHARK,
		GEO_FISHFOOD,

		GEO_SHARK_HAPPY,
		GEO_SHARK_CRAZY,

		//Assignment
		GEO_PATROLLER_PATROL,
		GEO_PATROLLER_ATTACKING,
		GEO_PATROLLER_DAMAGED,
		GEO_PATROLLER_DESTROYED,

		GEO_ENEMY,

		GEO_HARVESTER_MOVING,
		GEO_HARVESTER_ATTACKED,
		GEO_HARVESTER_DESTROYED,
		GEO_HARVESTER_HARVESTING,

		GEO_MINERAL,

		GEO_REPAIRER_MOVING,
		GEO_REPAIRER_ATTACKED,
		GEO_REPAIRER_DESTROYED,
		GEO_REPAIRER_REPAIRING,

		GEO_ENEMYBULLET,
		GEO_FRIENDLYBULLET,
		NUM_GEOMETRY,
	};
public:
	SceneBase();
	~SceneBase();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	void RenderMesh(Mesh *mesh, bool enableLight);
protected:
	unsigned m_vertexArrayID;
	Mesh* meshList[NUM_GEOMETRY];
	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];

	Camera camera;

	MS modelStack;
	MS viewStack;
	MS projectionStack;

	Light lights[1];

	bool bLightEnabled;

	float fps;

	int overfull;
	int deathByHunger;
	int deathByShark;
};

#endif