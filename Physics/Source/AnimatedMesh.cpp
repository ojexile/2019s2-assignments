#include "AnimatedMesh.h"

AnimatedMesh::AnimatedMesh(std::string sMeshName, int row, int col, int start, int end, float time, bool loop, Mesh* mesh)
	: m_col(col)
	, m_row(row)
	, m_currentTime(0)
	, m_currentFrame(0)
{
	m_Mesh = mesh;
	m_anim.Set(start, end, loop, time, true);
	m_bOriginal = true;
}
AnimatedMesh::AnimatedMesh(AnimatedMesh& ref)
{
	m_bOriginal = false;
	m_Mesh = ref.m_Mesh;
	m_row = ref.m_row;
	m_col = ref.m_col;
	m_currentFrame = 0;
	m_currentTime = 0;
	m_anim = ref.m_anim;
}
AnimatedMesh::~AnimatedMesh()
{
	if (m_bOriginal)
	{
		if (m_Mesh)
			delete m_Mesh;
	}
}
void AnimatedMesh::Update(double dt)
{
	if (m_anim.animActive)
	{
		// Get Anim time
		m_currentTime += static_cast<float>(dt);

		// Find num frame
		int numFrame = Math::Max(1, m_anim.endFrame - m_anim.startFrame + 1);
		float frameTime = m_anim.animTime / numFrame;

		// Get current frame
		m_currentFrame = Math::Min(m_anim.endFrame, m_anim.startFrame + (int)(m_currentTime / frameTime));

		// Check time
		if (m_currentTime >= m_anim.animTime)
		{
			// Repeat
			if (m_anim.repeatCount)
			{
				m_currentTime = 0.f;
				m_currentFrame = m_anim.startFrame;
			}

			// Don't Repeat
			else
			{
				m_anim.animActive = false;
				m_currentTime = 0.f;
				m_currentFrame = m_anim.startFrame;
			}
		}
	}
}
void AnimatedMesh::Render()
{
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, m_Mesh->vertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(Position));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Position) + sizeof(Color)));
	if (m_Mesh->m_uTextureArray[0] > 0)
	{
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Position) + sizeof(Color) + sizeof(Vector3)));
	}

	//glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Mesh->indexBuffer);

	//Draw------------------------------------------------------------------
	switch (m_Mesh->mode)
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
	if (m_Mesh->m_uTextureArray[0] > 0)
	{
		glDisableVertexAttribArray(3);
	}
	//==============================================================
}