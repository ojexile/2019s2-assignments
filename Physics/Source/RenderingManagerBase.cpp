#include "RenderingManagerBase.h"
#include "DataContainer.h"
#include "Locator.h"
#include "KeyboardManager.h"

#define FOG_ENABLED true

MS RenderingManagerBase::modelStack;
MS RenderingManagerBase::viewStack;
MS RenderingManagerBase::projectionStack;

RenderingManagerBase::RenderingManagerBase()
{
	m_fElapsedTime = 0;
	m_bFogEnabled = FOG_ENABLED;
}

RenderingManagerBase::~RenderingManagerBase()
{
}
void RenderingManagerBase::BindUniforms()
{
	// Get a handle for our uniform
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
	//m_parameters[U_MODEL] = glGetUniformLocation(m_programID, "M");
	//m_parameters[U_VIEW] = glGetUniformLocation(m_programID, "V");
	m_parameters[U_MODELVIEW] = glGetUniformLocation(m_programID, "MV");
	m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE] = glGetUniformLocation(m_programID, "MV_inverse_transpose");
	m_parameters[U_MATERIAL_AMBIENT] = glGetUniformLocation(m_programID, "material.kAmbient");
	m_parameters[U_MATERIAL_DIFFUSE] = glGetUniformLocation(m_programID, "material.kDiffuse");
	m_parameters[U_MATERIAL_SPECULAR] = glGetUniformLocation(m_programID, "material.kSpecular");
	m_parameters[U_MATERIAL_SHININESS] = glGetUniformLocation(m_programID, "material.kShininess");
	m_parameters[U_LIGHTENABLED] = glGetUniformLocation(m_programID, "lightEnabled");
	m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID, "numLights");

	// Get a handle for our "colorTexture" uniform
	m_parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(m_programID, "colorTextureEnabled");
	m_parameters[U_COLOR_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture");
	// Get a handle for our "textColor" uniform
	m_parameters[U_TEXT_ENABLED] = glGetUniformLocation(m_programID, "textEnabled");
	m_parameters[U_TEXT_COLOR] = glGetUniformLocation(m_programID, "textColor");

	// Fog
	m_parameters[U_FOG_COLOR] = glGetUniformLocation(m_programID, "fogParam.color");
	m_parameters[U_FOG_START] = glGetUniformLocation(m_programID, "fogParam.start");
	m_parameters[U_FOG_END] = glGetUniformLocation(m_programID, "fogParam.end");
	m_parameters[U_FOG_DENSITY] = glGetUniformLocation(m_programID, "fogParam.density");
	m_parameters[U_FOG_TYPE] = glGetUniformLocation(m_programID, "fogParam.type");
	m_parameters[U_FOG_ENABLED] = glGetUniformLocation(m_programID, "fogParam.enabled");

	m_parameters[U_FRAG_ET] = glGetUniformLocation(m_programID, "frag_et");
	m_parameters[U_VERT_ET] = glGetUniformLocation(m_programID, "vert_et");

	//texture
	m_parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(m_programID,
		"colorTextureEnabled[0]");
	m_parameters[U_COLOR_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture[0]");

	m_parameters[U_COLOR_TEXTURE_ENABLED1] = glGetUniformLocation(m_programID,
		"colorTextureEnabled[1]");
	m_parameters[U_COLOR_TEXTURE1] = glGetUniformLocation(m_programID, "colorTexture[1]");

	m_parameters[U_COLOR_TEXTURE_ENABLED1] = glGetUniformLocation(m_programID,
		"colorTextureEnabled[2]");
	m_parameters[U_COLOR_TEXTURE1] = glGetUniformLocation(m_programID, "colorTexture[2]");

	// Shadows
	m_parameters[U_LIGHT_DEPTH_MVP] =
		glGetUniformLocation(m_programID, "lightDepthMVP");
	m_parameters[U_SHADOW_MAP] = glGetUniformLocation(m_programID,
		"shadowMap");
	m_parameters[U_LIGHT_DEPTH_MVP_GPASS] =
		glGetUniformLocation(m_gPassShaderID, "lightDepthMVP");
	m_parameters[U_SHADOW_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(m_gPassShaderID, "colorTextureEnabled[0]");
	m_parameters[U_SHADOW_COLOR_TEXTURE] = glGetUniformLocation(m_gPassShaderID, "colorTexture[0]");
	m_parameters[U_SHADOW_COLOR_TEXTURE_ENABLED1] = glGetUniformLocation(m_gPassShaderID, "colorTextureEnabled[1]");
	m_parameters[U_SHADOW_COLOR_TEXTURE1] = glGetUniformLocation(m_gPassShaderID, "colorTexture[1]");
	m_parameters[U_SHADOW_COLOR_TEXTURE_ENABLED2] = glGetUniformLocation(m_gPassShaderID, "colorTextureEnabled[2]");
	m_parameters[U_SHADOW_COLOR_TEXTURE2] = glGetUniformLocation(m_gPassShaderID, "colorTexture[2]");

	//--------------------------------------------------------------------------------
	glUseProgram(m_programID);
	BindLightUniforms();
	//================================================================================
}
void RenderingManagerBase::BindLightUniforms()
{
	// Light================================================================================
	for (int i = 0; i < MAX_LIGHTS; ++i)
	{
		std::string prefix = "lights[" + std::to_string(i) + "].";
		m_LightParameters[U_LIGHT_TYPE + U_LIGHT_TOTAL * i] = glGetUniformLocation(m_programID, std::string(prefix + "type").c_str());
		m_LightParameters[U_LIGHT_POSITION + U_LIGHT_TOTAL * i] = glGetUniformLocation(m_programID, std::string(prefix + "position_cameraspace").c_str());
		m_LightParameters[U_LIGHT_COLOR + U_LIGHT_TOTAL * i] = glGetUniformLocation(m_programID, std::string(prefix + "color").c_str());
		m_LightParameters[U_LIGHT_POWER + U_LIGHT_TOTAL * i] = glGetUniformLocation(m_programID, std::string(prefix + "power").c_str());
		m_LightParameters[U_LIGHT_KC + U_LIGHT_TOTAL * i] = glGetUniformLocation(m_programID, std::string(prefix + "kC").c_str());
		m_LightParameters[U_LIGHT_KL + U_LIGHT_TOTAL * i] = glGetUniformLocation(m_programID, std::string(prefix + "kL").c_str());
		m_LightParameters[U_LIGHT_KQ + U_LIGHT_TOTAL * i] = glGetUniformLocation(m_programID, std::string(prefix + "kQ").c_str());
		m_LightParameters[U_LIGHT_SPOTDIRECTION + U_LIGHT_TOTAL * i] = glGetUniformLocation(m_programID, std::string(prefix + "spotDirection").c_str());
		m_LightParameters[U_LIGHT_COSCUTOFF + U_LIGHT_TOTAL * i] = glGetUniformLocation(m_programID, std::string(prefix + "cosCutoff").c_str());
		m_LightParameters[U_LIGHT_COSINNER + U_LIGHT_TOTAL * i] = glGetUniformLocation(m_programID, std::string(prefix + "cosInner").c_str());
		m_LightParameters[U_LIGHT_EXPONENT + U_LIGHT_TOTAL * i] = glGetUniformLocation(m_programID, std::string(prefix + "exponent").c_str());
	}
}
void RenderingManagerBase::SetUniforms(Scene* scene)
{
	// Init fog================================================================================
	Color fogColor{ 0.5f, 0.5f, 0.6f };
	glUniform3fv(m_parameters[U_FOG_COLOR], 1, &fogColor.r);
	glUniform1f(m_parameters[U_FOG_START], 30);
	glUniform1f(m_parameters[U_FOG_END], 100000);
	glUniform1f(m_parameters[U_FOG_DENSITY], 0.01f);
	glUniform1i(m_parameters[U_FOG_TYPE], 2);
	glUniform1i(m_parameters[U_FOG_ENABLED], m_bFogEnabled);

	// Shadows================================================================================
	glUniformMatrix4fv(m_parameters[U_LIGHT_DEPTH_MVP_GPASS], 1,
		GL_FALSE, &m_lightDepthMVPGPass.a[0]);
	glUniformMatrix4fv(m_parameters[U_LIGHT_DEPTH_MVP], 1,
		GL_FALSE, &m_lightDepthMVP.a[0]);

	glUniform1i(m_parameters[U_SHADOW_MAP], 8);

	glUniform1f(m_parameters[U_VERT_ET], m_fElapsedTime);
	glUniform1f(m_parameters[U_FRAG_ET], m_fElapsedTime);

	// Bind light global================================================================================
	glUniform1i(m_parameters[U_NUMLIGHTS], 2);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);

	// Light================================================================================
	for (unsigned index = 0; index < scene->GetLightManager()->GetSceneLights().size(); ++index)
	{
		Light* L = scene->GetLightManager()->GetSceneLights()[index];
		glUniform1i(m_LightParameters[U_LIGHT_TYPE + (U_LIGHT_TOTAL * index)], L->type);
		glUniform3fv(m_LightParameters[U_LIGHT_COLOR + (U_LIGHT_TOTAL * index)], 1, &L->color.r);
		glUniform1f(m_LightParameters[U_LIGHT_POWER + (U_LIGHT_TOTAL * index)], L->power);
		glUniform1f(m_LightParameters[U_LIGHT_KC + (U_LIGHT_TOTAL * index)], L->kC);
		glUniform1f(m_LightParameters[U_LIGHT_KL + (U_LIGHT_TOTAL * index)], L->kL);
		glUniform1f(m_LightParameters[U_LIGHT_KQ + (U_LIGHT_TOTAL * index)], L->kQ);
		glUniform1f(m_LightParameters[U_LIGHT_COSCUTOFF + (U_LIGHT_TOTAL * index)], L->cosCutoff);
		glUniform1f(m_LightParameters[U_LIGHT_COSINNER + (U_LIGHT_TOTAL * index)], L->cosInner);
		glUniform1f(m_LightParameters[U_LIGHT_EXPONENT + (U_LIGHT_TOTAL * index)], L->exponent);
	}
}

void RenderingManagerBase::Init()
{
	// Black background
	glClearColor(0.2f, 0.4f, 0.9f, 0.0f);
	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	glEnable(GL_CULL_FACE);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	// Shadows--------------------------------------------------------------------------------
	m_gPassShaderID = DataContainer::GetInstance()->GetShader("GPass");

	// Main Shader--------------------------------------------------------------------------------
	m_programID = DataContainer::GetInstance()->GetShader("Default");

	// Shadows
	m_lightDepthFBO.Init(2048, 2048);

	bLightEnabled = true;
	//BindUniforms();
	//SetUniforms();
}

void RenderingManagerBase::Update(double dt)
{
	//Keyboard Section
	// TODO SET DRAW MODE
	if (KeyboardManager::GetInstance()->GetKeyDown("EnableCull"))
		glEnable(GL_CULL_FACE);
	if (KeyboardManager::GetInstance()->GetKeyDown("DisableCull"))
		glDisable(GL_CULL_FACE);
	if (KeyboardManager::GetInstance()->GetKeyDown("DisableWireframe"))
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	if (KeyboardManager::GetInstance()->GetKeyDown("EnableWireframe"))
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// fps = (float)(1.f / dt);
	// CHENG_LOG("FPS: ", std::to_string(fps));
	m_fElapsedTime += (float)dt;
}

void RenderingManagerBase::RenderText(RenderComponent* rc)
{
	Mesh* mesh = rc->GetMesh();
	if (!mesh || mesh->m_uTextureArray[0] <= 0)
		return;
	std::string text = rc->GetText();
	Color color = rc->GetMaterial().kAmbient;
	glDisable(GL_DEPTH_TEST);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->m_uTextureArray[0]);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	for (unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 0.5f + 0.25f, 0.5f, 0);  //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	glEnable(GL_DEPTH_TEST);
}

void RenderingManagerBase::RenderTextOnScreen(RenderComponent* rc, std::string text, Color color, float size, float x, float y, int align)
{
	Mesh* mesh = rc->GetMesh();
	if (!mesh || mesh->m_uTextureArray[0] <= 0)
		return;

	glDisable(GL_DEPTH_TEST);
	Mtx44 ortho;
	ortho.SetToOrtho(0, 1920, 0, 1080, -100, 100);
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity();
	modelStack.PushMatrix();
	modelStack.LoadIdentity();
	modelStack.Translate(x - text.length() * 0.5f, y, 0);
	modelStack.Translate(text.length() * 0.5f * align, 0, 0);
	modelStack.Scale(size, size, size);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->m_uTextureArray[0]);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	for (unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 0.5f + 0.25f, 0.5f, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	modelStack.PopMatrix();
	viewStack.PopMatrix();
	projectionStack.PopMatrix();
	glEnable(GL_DEPTH_TEST);
}
void RenderingManagerBase::RenderUI(RenderComponent* rc, bool enableLight)
{
	Mesh* mesh;
	if (rc->GetMesh())
		mesh = rc->GetMesh();
	else if (rc->GetAnimatedMesh())
		mesh = rc->GetAnimatedMesh()->m_Mesh;

	Material mat = rc->GetMaterial();
	glDisable(GL_DEPTH_TEST);
	Mtx44 ortho;
	ortho.SetToOrtho(0, 1920, 0, 1080, -10, 10);
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity();

	Mtx44 MVP, modelView, modelView_inverse_transpose;

	//Shadows
	if (m_renderPass == RENDER_PASS_PRE)
	{
		/*Mtx44 lightDepthMVP = m_lightDepthProj *
			m_lightDepthView * modelStack.Top();
		glUniformMatrix4fv(m_parameters[U_LIGHT_DEPTH_MVP_GPASS], 1,
			GL_FALSE, &lightDepthMVP.a[0]);
		mesh->Render();*/
		return;
	}
	//--

	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	if (enableLight && bLightEnabled)
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 1);
		modelView = viewStack.Top() * modelStack.Top();
		glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);
		modelView_inverse_transpose = modelView.GetInverse().GetTranspose();
		glUniformMatrix4fv(m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE], 1, GL_FALSE, &modelView.a[0]);
		//Shadows--
		/*Mtx44 lightDepthMVP = m_lightDepthProj *
			m_lightDepthView * modelStack.Top();
		glUniformMatrix4fv(m_parameters[U_LIGHT_DEPTH_MVP], 1,
			GL_FALSE, &lightDepthMVP.a[0]);*/
			//--
			//load material
		glUniform3fv(m_parameters[U_MATERIAL_AMBIENT], 1, &mat.kAmbient.r);
		glUniform3fv(m_parameters[U_MATERIAL_DIFFUSE], 1, &mat.kDiffuse.r);
		glUniform3fv(m_parameters[U_MATERIAL_SPECULAR], 1, &mat.kSpecular.r);
		glUniform1f(m_parameters[U_MATERIAL_SHININESS], mat.kShininess);
	}
	else
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	}
	for (int i = 0; i < MAX_TEXTURES; ++i)
	{
		if (mesh->m_uTextureArray[i] > 0)
		{
			glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED + i], 1);
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, mesh->m_uTextureArray[i]);
			glUniform1i(m_parameters[U_COLOR_TEXTURE + i], i);
		}
		else
		{
			glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED + i], 0);
		}
	}
	mesh->Render();
	for (int i = 0; i < MAX_TEXTURES; ++i)
	{
		if (mesh->m_uTextureArray[i] > 0)
		{
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}
	projectionStack.PopMatrix();
	viewStack.PopMatrix();

	glEnable(GL_DEPTH_TEST);
}

void RenderingManagerBase::RenderMesh(RenderComponent *rc, bool enableLight)
{
	Mesh* mesh = rc->GetMesh();
	Material mat = rc->GetMaterial();
	Mtx44 MVP, modelView, modelView_inverse_transpose;
	glEnable(GL_DEPTH_TEST);
	//Shadows
	if (m_renderPass == RENDER_PASS_PRE)
	{
		m_lightDepthMVPGPass = m_lightDepthProj *
			m_lightDepthView * modelStack.Top();
		glUniformMatrix4fv(m_parameters[U_LIGHT_DEPTH_MVP_GPASS], 1,
			GL_FALSE, &m_lightDepthMVPGPass.a[0]);
		for (int i = 0; i < MAX_TEXTURES; ++i)
		{
			if (mesh->m_uTextureArray[i] > 0)
			{
				glUniform1i(m_parameters[U_SHADOW_COLOR_TEXTURE_ENABLED + i], 1);
				glActiveTexture(GL_TEXTURE0 + i);
				glBindTexture(GL_TEXTURE_2D, mesh->m_uTextureArray[i]);
				glUniform1i(m_parameters[U_SHADOW_COLOR_TEXTURE + i], i);
			}
			else
			{
				glUniform1i(m_parameters[U_SHADOW_COLOR_TEXTURE_ENABLED + i], 0);
			}
		}
		mesh->Render();

		return;
	}
	//--

	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	if (enableLight && bLightEnabled)
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 1);
		modelView = viewStack.Top() * modelStack.Top();
		glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);
		modelView_inverse_transpose = modelView.GetInverse().GetTranspose();
		glUniformMatrix4fv(m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE], 1, GL_FALSE, &modelView.a[0]);
		//Shadows--
		m_lightDepthMVP = m_lightDepthProj *
			m_lightDepthView * modelStack.Top();
		glUniformMatrix4fv(m_parameters[U_LIGHT_DEPTH_MVP], 1,
			GL_FALSE, &m_lightDepthMVP.a[0]);
		//--
		//load material
		glUniform3fv(m_parameters[U_MATERIAL_AMBIENT], 1, &mat.kAmbient.r);
		glUniform3fv(m_parameters[U_MATERIAL_DIFFUSE], 1, &mat.kDiffuse.r);
		glUniform3fv(m_parameters[U_MATERIAL_SPECULAR], 1, &mat.kSpecular.r);
		glUniform1f(m_parameters[U_MATERIAL_SHININESS], mat.kShininess);
	}
	else
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	}
	for (int i = 0; i < MAX_TEXTURES; ++i)
	{
		if (mesh->m_uTextureArray[i] > 0)
		{
			glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED + i], 1);
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, mesh->m_uTextureArray[i]);
			glUniform1i(m_parameters[U_COLOR_TEXTURE + i], i);
		}
		else
		{
			glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED + i], 0);
		}
	}
	mesh->Render();
	for (int i = 0; i < MAX_TEXTURES; ++i)
	{
		if (mesh->m_uTextureArray[i] > 0)
		{
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}
}

void RenderingManagerBase::RenderBiomedMesh(RenderComponent* rc, BiomeComponent *bc, bool enableLight)
{
	MeshBiomed* mesh = rc->GetMeshBiomed();
	Material mat = rc->GetMaterial();
	BiomeComponent::eBiomeTypes type = bc->GetBiomeType();

	Mtx44 MVP, modelView, modelView_inverse_transpose;
	glEnable(GL_DEPTH_TEST);
	//Shadows
	if (m_renderPass == RENDER_PASS_PRE)
	{
		m_lightDepthMVPGPass = m_lightDepthProj *
			m_lightDepthView * modelStack.Top();
		glUniformMatrix4fv(m_parameters[U_LIGHT_DEPTH_MVP_GPASS], 1,
			GL_FALSE, &m_lightDepthMVPGPass.a[0]);
		for (int i = 0; i < MAX_TEXTURES; ++i)
		{
			if (mesh->m_uBiomedTextureArray[type][i] > 0)
			{
				glUniform1i(m_parameters[U_SHADOW_COLOR_TEXTURE_ENABLED + i], 1);
				glActiveTexture(GL_TEXTURE0 + i);
				glBindTexture(GL_TEXTURE_2D, mesh->m_uBiomedTextureArray[type][i]);
				glUniform1i(m_parameters[U_SHADOW_COLOR_TEXTURE + i], i);
			}
			else
			{
				glUniform1i(m_parameters[U_SHADOW_COLOR_TEXTURE_ENABLED + i], 0);
			}
		}
		mesh->Render(type);

		return;
	}
	//--

	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	if (enableLight && bLightEnabled)
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 1);
		modelView = viewStack.Top() * modelStack.Top();
		glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);
		modelView_inverse_transpose = modelView.GetInverse().GetTranspose();
		glUniformMatrix4fv(m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE], 1, GL_FALSE, &modelView.a[0]);
		//Shadows--
		m_lightDepthMVP = m_lightDepthProj *
			m_lightDepthView * modelStack.Top();
		glUniformMatrix4fv(m_parameters[U_LIGHT_DEPTH_MVP], 1,
			GL_FALSE, &m_lightDepthMVP.a[0]);
		//--
		//load material
		glUniform3fv(m_parameters[U_MATERIAL_AMBIENT], 1, &mat.kAmbient.r);
		glUniform3fv(m_parameters[U_MATERIAL_DIFFUSE], 1, &mat.kDiffuse.r);
		glUniform3fv(m_parameters[U_MATERIAL_SPECULAR], 1, &mat.kSpecular.r);
		glUniform1f(m_parameters[U_MATERIAL_SHININESS], mat.kShininess);
	}
	else
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	}
	for (int i = 0; i < MAX_TEXTURES; ++i)
	{
		if (mesh->m_uBiomedTextureArray[type][i] > 0)
		{
			glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED + i], 1);
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, mesh->m_uBiomedTextureArray[type][i]);
			glUniform1i(m_parameters[U_COLOR_TEXTURE + i], i);
		}
		else
		{
			glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED + i], 0);
		}
	}
	mesh->Render(type);
	for (int i = 0; i < MAX_TEXTURES; ++i)
	{
		if (mesh->m_uBiomedTextureArray[type][i] > 0)
		{
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}
}

void RenderingManagerBase::RenderAnimatedMesh(RenderComponent *rc, bool enableLight)
{
	AnimatedMesh* anim = rc->GetAnimatedMesh();
	Material mat = rc->GetMaterial();
	Mtx44 MVP, modelView, modelView_inverse_transpose;
	glEnable(GL_DEPTH_TEST);
	//Shadows
	if (m_renderPass == RENDER_PASS_PRE)
	{
		m_lightDepthMVPGPass = m_lightDepthProj *
			m_lightDepthView * modelStack.Top();
		glUniformMatrix4fv(m_parameters[U_LIGHT_DEPTH_MVP_GPASS], 1,
			GL_FALSE, &m_lightDepthMVPGPass.a[0]);
		anim->m_Mesh->Render();
		return;
	}
	//--

	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	if (enableLight && bLightEnabled)
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 1);
		modelView = viewStack.Top() * modelStack.Top();
		glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);
		modelView_inverse_transpose = modelView.GetInverse().GetTranspose();
		glUniformMatrix4fv(m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE], 1, GL_FALSE, &modelView.a[0]);
		//Shadows--
		m_lightDepthMVP = m_lightDepthProj *
			m_lightDepthView * modelStack.Top();
		glUniformMatrix4fv(m_parameters[U_LIGHT_DEPTH_MVP], 1,
			GL_FALSE, &m_lightDepthMVP.a[0]);
		//--
		//load material
		glUniform3fv(m_parameters[U_MATERIAL_AMBIENT], 1, &mat.kAmbient.r);
		glUniform3fv(m_parameters[U_MATERIAL_DIFFUSE], 1, &mat.kDiffuse.r);
		glUniform3fv(m_parameters[U_MATERIAL_SPECULAR], 1, &mat.kSpecular.r);
		glUniform1f(m_parameters[U_MATERIAL_SHININESS], mat.kShininess);
	}
	else
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	}
	for (int i = 0; i < MAX_TEXTURES; ++i)
	{
		if (anim->m_Mesh->m_uTextureArray[i] > 0)
		{
			glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED + i], 1);
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, anim->m_Mesh->m_uTextureArray[i]);
			glUniform1i(m_parameters[U_COLOR_TEXTURE + i], i);
		}
		else
		{
			glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED + i], 0);
		}
	}
	anim->Render();
	for (int i = 0; i < MAX_TEXTURES; ++i)
	{
		if (anim->m_Mesh->m_uTextureArray[i] > 0)
		{
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}
}

void RenderingManagerBase::Render(Scene* scene)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderingManagerBase::Exit()
{
	// Cleanup VBO
	glDeleteProgram(m_programID);
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_gPassShaderID);
}