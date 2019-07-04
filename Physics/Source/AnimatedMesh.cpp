#include "AnimatedMesh.h"

AnimatedMesh::AnimatedMesh(std::string sMeshName, int row, int col)
	: Mesh(sMeshName)
	, m_col(col)
	, m_row(row)
	, m_currentTime(0)
	, m_currentFrame(0)
	, m_playCount(0)
{
	m_anim = NULL;
}

AnimatedMesh::~AnimatedMesh()
{
	if (m_anim)
		delete m_anim;
}
void AnimatedMesh::Update(double dt)
{
	if (m_anim->animActive)
	{
		// Get Anim time
		m_currentTime += static_cast<float>(dt);

		// Find num frame
		int numFrame = Math::Max(1, m_anim->endFrame - m_anim->startFrame);
		float frameTime = m_anim->animTime / numFrame;

		// Get current frame
		m_currentFrame = Math::Min(m_anim->endFrame, m_anim->startFrame + (int)(m_currentTime / frameTime));

		// Check time
		if (m_currentTime >= m_anim->animTime)
		{
			m_anim->ended = true;

			// Repeat
			if (m_anim->repeatCount == 0)
			{
				m_anim->animActive = false;
				m_currentTime = 0.f;
				m_currentFrame = m_anim->startFrame;
			}

			// Don't Repeat
			if (m_anim->repeatCount == 1)
			{
				m_currentTime = 0.f;
				m_currentFrame = m_anim->startFrame;
			}
		}
	}
}
void AnimatedMesh::Render(bool bEnableLight)
{
	//---------------------------------------------------------------------
	// Render VBO here
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_uiVertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	// Colour
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, m_uiColorBuffer);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//Normal
	if (bEnableLight)
	{
		glEnableVertexAttribArray(2); // 3rd attribute : normals
		glBindBuffer(GL_ARRAY_BUFFER, m_uiNormalBuffer);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
	}
	//Index
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_uiIndexBuffer);
	//Texture
	if (m_aTextureArray[0] > 0)
	{
		glEnableVertexAttribArray(3);
		glBindBuffer(GL_ARRAY_BUFFER, m_uiTexturesBuffer);
		glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0, 0);
	}
	//Draw------------------------------------------------------------------
	switch (mode)
	{
	case Mesh::DRAW_TRIANGLES:
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(m_currentFrame * 6 * sizeof(GLuint)));
		break;
	case Mesh::DRAW_TRIANGLE_STRIP:
		glDrawElements(GL_TRIANGLE_STRIP, 6, GL_UNSIGNED_INT, (void*)(m_currentFrame * 6 * sizeof(GLuint)));
		//glDrawArrays(GL_TRIANGLE_STRIP, 0, uiVertexSize);
		break;
	case Mesh::DRAW_LINE_STRIP:
		glDrawElements(GL_LINE_STRIP, 6, GL_UNSIGNED_INT, (void*)(m_currentFrame * 6 * sizeof(GLuint)));
		//glDrawArrays(GL_TRIANGLE_STRIP, 0, uiVertexSize);
		break;
	case Mesh::DRAW_TRIANGLE_FAN:
		glDrawElements(GL_TRIANGLE_FAN, 6, GL_UNSIGNED_INT, (void*)(m_currentFrame * 6 * sizeof(GLuint)));
		//glDrawArrays(GL_TRIANGLE_FAN, 0, uiVertexSize);
		break;
	case Mesh::DRAW_LINES:
		glDrawElements(GL_LINES, 6, GL_UNSIGNED_INT, (void*)(m_currentFrame * 6 * sizeof(GLuint)));
		break;
	case Mesh::DRAW_MODE_LAST:
		break;
	default:
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		break;
	}

	//Disable------------------------------------------------------------------
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	if (m_aTextureArray[0] > 0)
	{
		glDisableVertexAttribArray(3);
	}
	//==============================================================
}