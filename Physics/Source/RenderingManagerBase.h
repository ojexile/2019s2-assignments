#ifndef SCENE_BASE_H
#define SCENE_BASE_H

#include "Renderer.h"

#include "GL\glew.h"
#include "Mtx44.h"
#include "Camera.h"
#include "MatrixStack.h"
#include "Light.h"
#include "GameObject.h"
#include <vector>
#include "Mesh.h"
#include "Scene.h"

#include "shader.hpp"
#include "Utility.h"
#include "DepthFBO.h"
#include "MeshBuilder.h"

class RenderingManagerBase : public Renderer
{
protected:
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

		U_COLOR_TEXTURE_ENABLED,
		U_COLOR_TEXTURE_ENABLED1,
		U_COLOR_TEXTURE_ENABLED2,
		U_COLOR_TEXTURE_ENABLED3,
		U_COLOR_TEXTURE_ENABLED4,
		U_COLOR_TEXTURE_ENABLED5,
		U_COLOR_TEXTURE_ENABLED6,
		U_COLOR_TEXTURE_ENABLED7,

		U_COLOR_TEXTURE,
		U_COLOR_TEXTURE1,
		U_COLOR_TEXTURE2,
		U_COLOR_TEXTURE3,
		U_COLOR_TEXTURE4,
		U_COLOR_TEXTURE5,
		U_COLOR_TEXTURE6,
		U_COLOR_TEXTURE7,

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

		U_TEXT_ENABLED,
		U_TEXT_COLOR,

		// Fog
		U_FOG_COLOR,
		U_FOG_START,
		U_FOG_END,
		U_FOG_DENSITY,
		U_FOG_TYPE,
		U_FOG_ENABLED,
		U_FACTOR,

		U_FRAG_ET,
		U_VERT_ET,

		// Shadow
		U_LIGHT_DEPTH_MVP_GPASS,
		U_LIGHT_DEPTH_MVP,
		U_SHADOW_MAP,

		U_SHADOW_COLOR_TEXTURE,
		U_SHADOW_COLOR_TEXTURE1,
		U_SHADOW_COLOR_TEXTURE2,
		U_SHADOW_COLOR_TEXTURE_ENABLED,
		U_SHADOW_COLOR_TEXTURE_ENABLED1,
		U_SHADOW_COLOR_TEXTURE_ENABLED2,

		// flare
		U_FLARE_VAL,

		U_TOTAL,
	};
	enum RENDER_PASS
	{
		RENDER_PASS_PRE,
		RENDER_PASS_MAIN,
	};

public:
	RenderingManagerBase();
	virtual ~RenderingManagerBase();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render(Scene* scene);
	virtual void Exit();

protected:
	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	void RenderUI(Mesh* mesh, bool enableLight);
	void RenderMesh(Mesh *mesh, bool enableLight);
	void RenderAnimatedMesh(AnimatedMesh *mesh, bool enableLight);
	void BindUniforms();

	unsigned m_vertexArrayID;
	unsigned m_programID;
	int m_parameters[U_TOTAL];

	MS modelStack;
	MS viewStack;
	MS projectionStack;

	Light lights[1];
	bool bLightEnabled;
	float fps;
	float m_fElapsedTime;

	float m_fFlareVal;

	bool m_bFogEnabled;

	// Shadow
	unsigned m_gPassShaderID;
	DepthFBO m_lightDepthFBO;
	Mtx44 m_lightDepthProj;
	Mtx44 m_lightDepthView;
	Mtx44 m_lightDepthMVP;
	Mtx44 m_lightDepthMVPGPass;
	RENDER_PASS m_renderPass;
};

#endif