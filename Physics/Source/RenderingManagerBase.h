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
#include "MeshBiomed.h"
#include "Scene.h"

#include "shader.hpp"
#include "Utility.h"
#include "DepthFBO.h"
#include "MeshBuilder.h"
#include "RenderComponent.h"
#define FOG_ENABLED true
#define MAX_LIGHTS 8

class RenderingManagerBase : public Renderer
{
public:
	enum UNIFORM_TYPE
	{
		U_MVP = 0,
		U_MODELVIEW,
		U_MODELVIEW_INVERSE_TRANSPOSE,
		U_MATERIAL_AMBIENT,
		U_MATERIAL_DIFFUSE,
		U_MATERIAL_SPECULAR,
		U_MATERIAL_SHININESS,
		U_ALPHA,
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
		// Text
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

		U_SHADOW_COLOR_TEXTURE_ENABLED,
		U_SHADOW_COLOR_TEXTURE,
		U_SHADOW_COLOR_TEXTURE_ENABLED1,
		U_SHADOW_COLOR_TEXTURE1,
		U_SHADOW_COLOR_TEXTURE_ENABLED2,
		U_SHADOW_COLOR_TEXTURE2,

		U_POST_TEXTURE,
		U_POST2_TEXTURE,

		// extra
		U_DIST_FROM_PLAYER,
		U_VIGINETTE_VAL,

		U_EFFECT0_INTENSITY,
		U_EFFECT1_INTENSITY,
		U_EFFECT1_TIME,
		U_EFFECT2_TIME,
		U_EFFECT2_INTENSITY,
		U_EFFECT2_STATIC_FADE,

		U_TOTAL,
	};
	enum UNIFORM_LIGHT
	{
		U_LIGHT_TYPE,
		U_LIGHT_POSITION,
		U_LIGHT_COLOR,
		U_LIGHT_POWER,
		U_LIGHT_KC,
		U_LIGHT_KL,
		U_LIGHT_KQ,
		U_LIGHT_SPOTDIRECTION,
		U_LIGHT_COSCUTOFF,
		U_LIGHT_COSINNER,
		U_LIGHT_EXPONENT,

		U_LIGHT_TOTAL,
	};
	enum RENDER_PASS
	{
		RENDER_PASS_PRE,
		RENDER_PASS_MAIN,
		RENDER_PASS_POST,
		RENDER_PASS_POST_2,
	};

public:
	RenderingManagerBase();
	virtual ~RenderingManagerBase();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render(Scene* scene);
	virtual void Exit();
	virtual void Resize(Vector3 size);
protected:
	void RenderText(RenderComponent* mesh);
	void RenderTextOnScreen(RenderComponent* rc, std::string text, Color color, float size, float x, float y, int align = 0);
	void RenderUI(RenderComponent* mesh, bool enableLight);
	void RenderMesh(RenderComponent *mesh, bool enableLight);
	void RenderBiomedMesh(RenderComponent*mesh, BiomeComponent *bc, bool enableLight);
	void RenderAnimatedMesh(RenderComponent *mesh, bool enableLight);
	void BindUniforms();
	void SetUniforms(Scene* scene);
	void BindLightUniforms();

	unsigned m_vertexArrayID;
	unsigned m_programID;
	unsigned m_PostProcessProgram;
	unsigned m_PostProcessProgram2;
	int m_parameters[U_TOTAL];
	int m_LightParameters[U_LIGHT_TOTAL * MAX_LIGHTS];

	static MS modelStack;
	static MS viewStack;
	static MS projectionStack;

	bool bLightEnabled;
	float fps;
	float m_fElapsedTime;

	bool m_bFogEnabled;

	// Shadow
	unsigned m_gPassShaderID;
	DepthFBO m_lightDepthFBO;
	Mtx44 m_lightDepthProj;
	Mtx44 m_lightDepthView;
	Mtx44 m_lightDepthMVP;
	Mtx44 m_lightDepthMVPGPass;
	RENDER_PASS m_renderPass;
public:
	void SetUniform1f(UNIFORM_TYPE, float f);
};

#endif