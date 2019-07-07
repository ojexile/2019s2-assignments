#include "AnimatedMesh.h"

AnimatedMesh::AnimatedMesh(std::string sMeshName, int row, int col, int start, int end, float time, bool loop)
	: Mesh(sMeshName)
	, m_col(col)
	, m_row(row)
	, m_currentTime(0)
	, m_currentFrame(0)
	, m_playCount(0)
{
	m_anim = new Animation();
	m_anim->Set(start, end, loop, time, true);
}
AnimatedMesh::AnimatedMesh(AnimatedMesh& mesh)
	:Mesh(mesh.name)
{
	m_row = mesh.m_row;
	m_col = mesh.m_col;
	m_currentFrame = 0;
	m_currentFrame = 0;
	m_playCount = 0;
	m_anim = new Animation();
	m_anim->Set(mesh.m_anim->startFrame, mesh.m_anim->endFrame, mesh.m_anim->repeatCount, mesh.m_anim->animTime, mesh.m_anim->animActive);
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
		int numFrame = Math::Max(1, m_anim->endFrame - m_anim->startFrame + 1);
		float frameTime = m_anim->animTime / numFrame;

		// Get current frame
		m_currentFrame = Math::Min(m_anim->endFrame, m_anim->startFrame + (int)(m_currentTime / frameTime));

		// Check time
		if (m_currentTime >= m_anim->animTime)
		{
			// Repeat
			if (m_anim->repeatCount)
			{
				m_currentTime = 0.f;
				m_currentFrame = m_anim->startFrame;
			}

			// Don't Repeat
			else
			{
				m_anim->animActive = false;
				m_currentTime = 0.f;
				m_currentFrame = m_anim->startFrame;
			}
		}
	}
}
void AnimatedMesh::Render()
{
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(Position));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Position) + sizeof(Color)));
	if (m_uTextureArray[0] > 0)
	{
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Position) + sizeof(Color) + sizeof(Vector3)));
	}

	//glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

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
	if (m_uTextureArray[0] > 0)
	{
		glDisableVertexAttribArray(3);
	}
	//==============================================================
}