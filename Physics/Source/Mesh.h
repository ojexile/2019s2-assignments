#ifndef MESH_H
#define MESH_H
#define MAX_TEXTURES 8
#include <string>
#include "Material.h"
#include "Vertex.h"

#include <string>

class Mesh
{
protected:
	int m_iNumTextures;
	unsigned m_uTextureArray[MAX_TEXTURES];
public:
	enum DRAW_MODE
	{
		DRAW_TRIANGLES, //default mode
		DRAW_TRIANGLE_STRIP,
		DRAW_LINES,
		DRAW_MODE_LAST,
	};
	Mesh(const std::string &meshName);
	virtual ~Mesh();
	virtual void Render();
	virtual void Render(unsigned offset, unsigned count);

	const std::string name;
	DRAW_MODE mode;
	unsigned vertexBuffer;
	unsigned indexBuffer;
	unsigned indexSize;

	Mesh* SetTexture(unsigned i);
	Mesh* AddTexture(unsigned i);
	Mesh* AddTexture(std::string s);

	friend class AnimatedMesh;
	friend class RenderingManagerBase;
};

#endif