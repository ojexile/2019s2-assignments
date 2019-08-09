#include "MeshBuilder.h"
#include <GL\glew.h>
#include <vector>
#include "Vertex.h"
#include "MyMath.h"
#include "LoadOBJ.h"
#include "Resources.h"
#include "Preferences.h"

/******************************************************************************/
/*!
\brief
Generate the vertices of a reference Axes; Use red for x-axis, green for y-axis, blue for z-axis
Then generate the VBO/IBO and store them in Mesh object

\param meshName - name of mesh
\param lengthX - x-axis should start at -lengthX / 2 and end at lengthX / 2
\param lengthY - y-axis should start at -lengthY / 2 and end at lengthY / 2
\param lengthZ - z-axis should start at -lengthZ / 2 and end at lengthZ / 2

\return Pointer to mesh storing VBO/IBO of reference axes
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateAxes(const std::string &meshName, float lengthX, float lengthY, float lengthZ)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	v.pos.Set(-1000, 0, 0);
	v.color.Set(1, 0, 0);
	vertex_buffer_data.push_back(v);
	v.pos.Set(1000, 0, 0);
	v.color.Set(1, 0, 0);
	vertex_buffer_data.push_back(v);
	v.pos.Set(0, -1000, 0);
	v.color.Set(0, 1, 0);
	vertex_buffer_data.push_back(v);
	v.pos.Set(0, 1000, 0);
	v.color.Set(0, 1, 0);
	vertex_buffer_data.push_back(v);
	v.pos.Set(0, 0, -1000);
	v.color.Set(0, 0, 1);
	vertex_buffer_data.push_back(v);
	v.pos.Set(0, 0, 1000);
	v.color.Set(0, 0, 1);
	vertex_buffer_data.push_back(v);

	std::vector<GLuint> index_buffer_data;
	index_buffer_data.push_back(0);
	index_buffer_data.push_back(1);
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(3);
	index_buffer_data.push_back(4);
	index_buffer_data.push_back(5);

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_LINES;

	return mesh;
}

/******************************************************************************/
/*!
\brief
Generate the vertices of a quad; Use random color for each vertex
Then generate the VBO/IBO and store them in Mesh object

\param meshName - name of mesh
\param lengthX - width of quad
\param lengthY - height of quad

\return Pointer to mesh storing VBO/IBO of quad
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateQuad(const std::string &meshName, Color color, float length)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	v.pos.Set(-0.5f * length, -0.5f * length, 0);
	v.color = color;
	v.normal.Set(0, 0, 1);
	v.texCoord.Set(0, 0);
	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * length, -0.5f * length, 0);
	v.color = color;
	v.normal.Set(0, 0, 1);
	v.texCoord.Set(1.0f, 0);
	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * length, 0.5f * length, 0);
	v.color = color;
	v.normal.Set(0, 0, 1);
	v.texCoord.Set(1.0f, 1.0f);
	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * length, 0.5f * length, 0);
	v.color = color;
	v.normal.Set(0, 0, 1);
	v.texCoord.Set(0, 1.0f);
	vertex_buffer_data.push_back(v);

	index_buffer_data.push_back(3);
	index_buffer_data.push_back(0);
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(1);
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(0);

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLES;

	return mesh;
}
Mesh* MeshBuilder::GenerateQuadLeftCentered(Color color, float length)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	v.pos.Set(0, -length / 2, 0);	// bl
	v.color = color;
	v.normal.Set(0, 0, 1);
	v.texCoord.Set(0, 0);
	vertex_buffer_data.push_back(v);
	v.pos.Set(length, -0.5f * length, 0);	// br
	v.color = color;
	v.normal.Set(0, 0, 1);
	v.texCoord.Set(1.0f, 0);
	vertex_buffer_data.push_back(v);
	v.pos.Set(length, 0.5f * length, 0);		// tr
	v.color = color;
	v.normal.Set(0, 0, 1);
	v.texCoord.Set(1.0f, 1.0f);
	vertex_buffer_data.push_back(v);
	v.pos.Set(0, 0.5f * length, 0);	//tl
	v.color = color;
	v.normal.Set(0, 0, 1);
	v.texCoord.Set(0, 1.0f);
	vertex_buffer_data.push_back(v);

	index_buffer_data.push_back(3);
	index_buffer_data.push_back(0);
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(1);
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(0);

	Mesh *mesh = new Mesh("Misc");

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLES;

	return mesh;
}

/******************************************************************************/
/*!
\brief
Generate the vertices of a cube; Use random color for each vertex
Then generate the VBO/IBO and store them in Mesh object

\param meshName - name of mesh
\param lengthX - width of cube
\param lengthY - height of cube
\param lengthZ - depth of cube

\return Pointer to mesh storing VBO/IBO of cube
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateCube(const std::string &meshName, Color color, float length)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;

	v.pos.Set(-0.5f * length, -0.5f * length, -0.5f * length);
	v.color = color;
	v.normal = Vector3{ -1, -1, -1 }.Normalize();
	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * length, -0.5f * length, -0.5f * length);
	v.color = color;
	v.normal = Vector3{ 1, -1, -1 }.Normalize();
	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * length, 0.5f * length, -0.5f * length);
	v.color = color;
	v.normal = Vector3{ 1, 1, -1 }.Normalize();
	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * length, 0.5f * length, -0.5f * length);
	v.color = color;
	v.normal = Vector3{ -1, 1, -1 }.Normalize();
	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * length, -0.5f * length, 0.5f * length);
	v.color = color;
	v.normal = Vector3{ -1, -1, 1 }.Normalize();
	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * length, -0.5f * length, 0.5f * length);
	v.color = color;
	v.normal = Vector3{ 1, -1, 1 }.Normalize();
	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * length, 0.5f * length, 0.5f * length);
	v.color = color;
	v.normal = Vector3{ 1, 1, 1 }.Normalize();
	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * length, 0.5f * length, 0.5f * length);
	v.color = color;
	v.normal = Vector3{ -1, 1, 1 }.Normalize();
	vertex_buffer_data.push_back(v);

	std::vector<GLuint> index_buffer_data;
	index_buffer_data.push_back(7);
	index_buffer_data.push_back(4);
	index_buffer_data.push_back(6);
	index_buffer_data.push_back(5);
	index_buffer_data.push_back(6);
	index_buffer_data.push_back(4);
	index_buffer_data.push_back(6);
	index_buffer_data.push_back(5);
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(1);
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(5);
	index_buffer_data.push_back(3);
	index_buffer_data.push_back(7);
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(6);
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(7);
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(1);
	index_buffer_data.push_back(3);
	index_buffer_data.push_back(0);
	index_buffer_data.push_back(3);
	index_buffer_data.push_back(1);
	index_buffer_data.push_back(3);
	index_buffer_data.push_back(0);
	index_buffer_data.push_back(7);
	index_buffer_data.push_back(4);
	index_buffer_data.push_back(7);
	index_buffer_data.push_back(0);
	index_buffer_data.push_back(1);
	index_buffer_data.push_back(5);
	index_buffer_data.push_back(0);
	index_buffer_data.push_back(4);
	index_buffer_data.push_back(0);
	index_buffer_data.push_back(5);

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = 36;
	mesh->mode = Mesh::DRAW_TRIANGLES;

	return mesh;
}

Mesh* MeshBuilder::GenerateRing(const std::string &meshName, Color color, unsigned numSlice, float outerR, float innerR)
{
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	Vertex v;

	float degreePerSlice = 360.f / numSlice;
	//float radianPerSlice = Math::DegreeToRadian(360.f) / numSlice;
	for (unsigned slice = 0; slice < numSlice + 1; ++slice)
	{
		float theta = slice * degreePerSlice;
		v.color = color;
		v.normal.Set(0, 1, 0);
		v.pos.Set(outerR * cos(Math::DegreeToRadian(theta)), 0, outerR * sin(Math::DegreeToRadian(theta)));
		vertex_buffer_data.push_back(v);

		v.color = color;
		v.normal.Set(0, 1, 0);
		v.pos.Set(innerR * cos(Math::DegreeToRadian(theta)), 0, innerR * sin(Math::DegreeToRadian(theta)));
		vertex_buffer_data.push_back(v);
	}
	for (unsigned slice = 0; slice < numSlice + 1; ++slice)
	{
		index_buffer_data.push_back(2 * slice + 0);
		index_buffer_data.push_back(2 * slice + 1);
		//index_buffer_data.push_back(2 * slice + 3);
		//index_buffer_data.push_back(2 * slice + 4);
		//index_buffer_data.push_back(2 * slice + 3);
		//index_buffer_data.push_back(2 * slice + 2);
	}

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	mesh->indexSize = index_buffer_data.size();

	return mesh;
}

float sphereX(float phi, float theta)
{
	return cos(Math::DegreeToRadian(phi)) * cos(Math::DegreeToRadian(theta));
}
float sphereY(float phi, float theta)
{
	return sin(Math::DegreeToRadian(phi));
}
float sphereZ(float phi, float theta)
{
	return cos(Math::DegreeToRadian(phi)) * sin(Math::DegreeToRadian(theta));
}

Mesh* MeshBuilder::GenerateSphere(const std::string &meshName, Color color, unsigned numStack, unsigned numSlice, float radius)
{
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	float degreePerStack = 180.f / numStack;
	float degreePerSlice = 360.f / numSlice;
	//float radianPerSlice = Math::DegreeToRadian(360.f) / numSlice;

	for (unsigned stack = 0; stack < numStack + 1; ++stack) //stack //replace with 180 for sphere
	{
		float phi = -90.f + stack * degreePerStack;
		for (unsigned slice = 0; slice < numSlice + 1; ++slice) //slice
		{
			float theta = slice * degreePerSlice;
			Vertex v;
			v.pos.Set(radius * sphereX(phi, theta), radius * sphereY(phi, theta), radius * sphereZ(phi, theta));
			v.color = color;
			v.normal.Set(sphereX(phi, theta), sphereY(phi, theta), sphereZ(phi, theta));
			vertex_buffer_data.push_back(v);
		}
	}
	for (unsigned stack = 0; stack < numStack; ++stack)
	{
		for (unsigned slice = 0; slice < numSlice + 1; ++slice)
		{
			index_buffer_data.push_back((numSlice + 1) * stack + slice + 0);
			index_buffer_data.push_back((numSlice + 1) * (stack + 1) + slice + 0);
			//index_buffer_data.push_back((numSlice + 1) * stack + slice + 1);
			//index_buffer_data.push_back((numSlice + 1) * (stack + 1) + slice + 1);
			//index_buffer_data.push_back((numSlice + 1) * stack + slice + 1);
			//index_buffer_data.push_back((numSlice + 1) * (stack + 1) + slice + 0);
		}
	}

	Mesh *mesh = new Mesh(meshName);

	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();

	return mesh;
}

Mesh* MeshBuilder::GenerateCone(const std::string &meshName, Color color, unsigned numSlice, float radius, float height)
{
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	Vertex v;
	float degreePerSlice = 360.f / numSlice;

	for (unsigned slice = 0; slice < numSlice + 1; ++slice) //slice
	{
		float theta = slice * degreePerSlice;
		Vector3 normal(height * cos(Math::DegreeToRadian(theta)), radius, height * sin(Math::DegreeToRadian(theta)));
		normal.Normalize();

		v.pos.Set(radius * cos(Math::DegreeToRadian(theta)), 0, radius * sin(Math::DegreeToRadian(theta)));
		v.color = color;
		v.normal = normal;
		vertex_buffer_data.push_back(v);

		v.pos.Set(0, height, 0);
		v.color = color;
		v.normal = normal;
		vertex_buffer_data.push_back(v);
	}
	for (unsigned slice = 0; slice < numSlice + 1; ++slice)
	{
		index_buffer_data.push_back(slice * 2 + 0);
		index_buffer_data.push_back(slice * 2 + 1);
	}

	Mesh *mesh = new Mesh(meshName);

	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();

	return mesh;
}
Mesh* MeshBuilder::GenerateOBJ(std::string name)
{
	std::vector<Position> vertices;
	std::vector<TexCoord> uvs;
	std::vector<Vector3> normals;

	std::string sQuality = Preferences::GetPref(Resources::PreferencesTerm::Quality);
	std::ifstream fileStream;
	if (sQuality == "HIGH")
	{
		std::string file_path = Resources::Path::Object + sQuality + '/' + name + ".obj";
		bool success = LoadOBJ(file_path.c_str(), vertices, uvs, normals);
		if (!success)
		{
			DEFAULT_LOG("Unable to load obj of: " + name + "for HIGH preset.");
			return NULL;
		}
	}
	else if (sQuality == "LOW")
	{
		std::string file_path = Resources::Path::Object + name + ".obj";
		bool success = LoadOBJ(file_path.c_str(), vertices, uvs, normals);
		if (!success)
		{
			std::string file_path = Resources::Path::Object + "HIGH" + '/' + name + ".obj";
			bool success = LoadOBJ(file_path.c_str(), vertices, uvs, normals);
			if (!success)
			{
				DEFAULT_LOG("Unable to load obj of: " + name + "for LOW & HIGH preset.");
				return NULL;
			}
		}
	}
	else
		DEFAULT_LOG("Unknown quality type of: " + sQuality);

	std::string file_path = Resources::Path::Object + name + ".obj";
	bool success = LoadOBJ(file_path.c_str(), vertices, uvs, normals);
	if (!success)
		return NULL;

	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	IndexVBO(vertices, uvs, normals, index_buffer_data, vertex_buffer_data, { 1,1,1 });

	Mesh *mesh = new Mesh(name);

	mesh->mode = Mesh::DRAW_TRIANGLES;

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();

	return mesh;
}

Mesh* MeshBuilder::GenerateText(const std::string &meshName, unsigned numRow, unsigned numCol)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	float width = 1.f / numCol;
	float height = 1.f / numRow;
	int offset = 0;
	for (unsigned i = 0; i < numRow; ++i)
	{
		for (unsigned j = 0; j < numCol; ++j)
		{
			float u1 = j * width;
			float v1 = 1.f - height - i * height;
			v.pos.Set(-0.5f, -0.5f, 0);
			v.texCoord.Set(u1, v1);
			vertex_buffer_data.push_back(v);

			v.pos.Set(0.5f, -0.5f, 0);
			v.texCoord.Set(u1 + width, v1);
			vertex_buffer_data.push_back(v);

			v.pos.Set(0.5f, 0.5f, 0);
			v.texCoord.Set(u1 + width, v1 + height);
			vertex_buffer_data.push_back(v);

			v.pos.Set(-0.5f, 0.5f, 0);
			v.texCoord.Set(u1, v1 + height);
			vertex_buffer_data.push_back(v);

			index_buffer_data.push_back(offset + 0);
			index_buffer_data.push_back(offset + 1);
			index_buffer_data.push_back(offset + 2);
			index_buffer_data.push_back(offset + 0);
			index_buffer_data.push_back(offset + 2);
			index_buffer_data.push_back(offset + 3);
			offset += 4;
		}
	}

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLES;

	return mesh;
}

Mesh* MeshBuilder::GenerateTerrain(const std::string &meshName, std::string file_path, std::vector<unsigned char> &heightMap, Vector3 terrainScale)
{
	file_path = Resources::Path::HeightMap + file_path + ".raw";
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	const float SCALE_FACTOR = 256.f;
	if (!LoadHeightMap(file_path.c_str(), heightMap))
		return NULL;

	unsigned terrainSize = (unsigned)sqrt((double)heightMap.size());

	Mtx44 scale;
	scale.SetToScale(terrainScale.x, terrainScale.y, terrainScale.z);
	for (unsigned z = 0; z < terrainSize; ++z)
	{
		for (unsigned x = 0; x < terrainSize; ++x)
		{
			float scaledHeight = (float)heightMap[z * terrainSize + x] / SCALE_FACTOR;
			v.pos.Set(static_cast<float>(x) / terrainSize - 0.5f, scaledHeight, static_cast<float>(z) / terrainSize - 0.5f);
			Vector3 vPos = { v.pos.x, v.pos.y,v.pos.z };
			vPos.y -= .4f; // offset so that mid gray is at 0
			vPos = scale * vPos;
			//vPos.y = roundf(vPos.y);
			v.pos.Set(vPos.x, vPos.y, vPos.z);
			v.color.Set(scaledHeight, scaledHeight, scaledHeight);
			v.normal.Set(0, 1, 0);
			v.texCoord.Set((float)x / terrainSize * 8, 1.f - (float)z / terrainSize * 8);
			vertex_buffer_data.push_back(v);
		}
	}

	for (unsigned z = 0; z < terrainSize - 1; ++z)
	{
		for (unsigned x = 0; x < terrainSize - 1; ++x)
		{
			index_buffer_data.push_back(terrainSize * z + x + 0);
			index_buffer_data.push_back(terrainSize * (z + 1) + x + 0);
			index_buffer_data.push_back(terrainSize * z + x + 1);

			index_buffer_data.push_back(terrainSize * (z + 1) + x + 1);
			index_buffer_data.push_back(terrainSize * z + x + 1);
			index_buffer_data.push_back(terrainSize * (z + 1) + x + 0);
		}
	}
	// NORMALS
	terrainScale.y = terrainScale.y / (terrainScale.x / terrainScale.y);
	for (unsigned int x = 0; x < vertex_buffer_data.size(); ++x)
	{
		if (x == 0) //for very first vert only
		{
			Vector3 AdjVert1 = Vector3(vertex_buffer_data[x + 1].pos.x * terrainScale.x, vertex_buffer_data[x + 1].pos.y * terrainScale.y, vertex_buffer_data[x + 1].pos.z * terrainScale.z);
			Vector3 currVert = Vector3(vertex_buffer_data[x].pos.x * terrainScale.x, vertex_buffer_data[x].pos.y * terrainScale.y, vertex_buffer_data[x].pos.z * terrainScale.z);
			Vector3 Vec1 = AdjVert1 - currVert;

			Vector3 AdjVert2 = Vector3(vertex_buffer_data[x + terrainSize].pos.x * terrainScale.x, vertex_buffer_data[x + terrainSize].pos.y * terrainScale.y, vertex_buffer_data[x + terrainSize].pos.z * terrainScale.z);
			Vector3 Vec2 = AdjVert2 - currVert;

			Vector3 temp = Vec1.Cross(Vec2);
			if (temp.y < 0)
				temp *= -1;
			vertex_buffer_data[x].normal.Set(temp.x, temp.y, temp.z);
		}
		else if (x == (terrainSize - 1)) //top rightt corner vert special case
		{
			Vector3 AdjVert1 = Vector3(vertex_buffer_data[x - 1].pos.x * terrainScale.x, vertex_buffer_data[x - 1].pos.y * terrainScale.y, vertex_buffer_data[x - 1].pos.z * terrainScale.z);
			Vector3 currVert = Vector3(vertex_buffer_data[x].pos.x * terrainScale.x, vertex_buffer_data[x].pos.y * terrainScale.y, vertex_buffer_data[x].pos.z * terrainScale.z);
			Vector3 Vec1 = AdjVert1 - currVert;

			Vector3 AdjVert2 = Vector3(vertex_buffer_data[x + terrainSize].pos.x * terrainScale.x, vertex_buffer_data[x + terrainSize].pos.y * terrainScale.y, vertex_buffer_data[x + terrainSize].pos.z * terrainScale.z);
			Vector3 Vec2 = AdjVert2 - currVert;

			Vector3 temp = Vec1.Cross(Vec2);
			if (temp.y < 0)
				temp *= -1;

			vertex_buffer_data[x].normal.Set(temp.x, temp.y, temp.z);
		}
		else if (x == (vertex_buffer_data.size() - terrainSize)) //bottom left corner vert special case
		{
			Vector3 AdjVert1 = Vector3(vertex_buffer_data[x + 1].pos.x * terrainScale.x, vertex_buffer_data[x + 1].pos.y * terrainScale.y, vertex_buffer_data[x + 1].pos.z * terrainScale.z);
			Vector3 currVert = Vector3(vertex_buffer_data[x].pos.x * terrainScale.x, vertex_buffer_data[x].pos.y * terrainScale.y, vertex_buffer_data[x].pos.z * terrainScale.z);
			Vector3 Vec1 = AdjVert1 - currVert;

			Vector3 AdjVert2 = Vector3(vertex_buffer_data[x - terrainSize].pos.x * terrainScale.x, vertex_buffer_data[x - terrainSize].pos.y * terrainScale.y, vertex_buffer_data[x - terrainSize].pos.z * terrainScale.z);
			Vector3 Vec2 = AdjVert2 - currVert;

			Vector3 temp = Vec1.Cross(Vec2);
			if (temp.y < 0)
				temp *= -1;

			vertex_buffer_data[x].normal.Set(temp.x, temp.y, temp.z);
		}
		else if (x == vertex_buffer_data.size() - 1) //For bottom right last vert special case
		{
			Vector3 AdjVert1 = Vector3(vertex_buffer_data[x - 1].pos.x * terrainScale.x, vertex_buffer_data[x - 1].pos.y * terrainScale.y, vertex_buffer_data[x - 1].pos.z * terrainScale.z);
			Vector3 currVert = Vector3(vertex_buffer_data[x].pos.x * terrainScale.x, vertex_buffer_data[x].pos.y * terrainScale.y, vertex_buffer_data[x].pos.z * terrainScale.z);
			Vector3 Vec1 = AdjVert1 - currVert;

			Vector3 AdjVert2 = Vector3(vertex_buffer_data[x - terrainSize].pos.x * terrainScale.x, vertex_buffer_data[x - terrainSize].pos.y * terrainScale.y, vertex_buffer_data[x - terrainSize].pos.z * terrainScale.z);
			Vector3 Vec2 = AdjVert2 - currVert;

			Vector3 temp = Vec1.Cross(Vec2);
			if (temp.y < 0)
				temp *= -1;
			vertex_buffer_data[x].normal.Set(temp.x, temp.y, temp.z);
		}
		else if ((x % terrainSize) == 0 && x != 0 && x != (vertex_buffer_data.size() - terrainSize)) //special case for first vertices of all rows excluding first vert and bottom left vert
		{
			Vector3 currVert = Vector3(vertex_buffer_data[x].pos.x * terrainScale.x, vertex_buffer_data[x].pos.y * terrainScale.y, vertex_buffer_data[x].pos.z * terrainScale.z);
			Vector3 AdjVert1 = Vector3(vertex_buffer_data[x - terrainSize].pos.x * terrainScale.x, vertex_buffer_data[x - terrainSize].pos.y * terrainScale.y, vertex_buffer_data[x - terrainSize].pos.z * terrainScale.z);
			Vector3 AdjVert2 = Vector3(vertex_buffer_data[x + terrainSize].pos.x * terrainScale.x, vertex_buffer_data[x + terrainSize].pos.y * terrainScale.y, vertex_buffer_data[x + terrainSize].pos.z * terrainScale.z);
			Vector3 AdjVert3 = Vector3(vertex_buffer_data[x + 1].pos.x * terrainScale.x, vertex_buffer_data[x + 1].pos.y * terrainScale.y, vertex_buffer_data[x + 1].pos.z * terrainScale.z); //right vert

			Vector3 Vec1 = AdjVert1 - currVert;
			Vector3 Vec2 = AdjVert2 - currVert;
			Vector3 Vec3 = AdjVert3 - currVert; //right vect

			Vector3 temp = Vector3(0, 0, 0);
			Vector3 temp1 = Vec1.Cross(Vec3);
			Vector3 temp2 = Vec2.Cross(Vec3);

			if (temp1.y < 0)
			{
				temp1 *= -1;
				temp += temp1;
			}
			else
				temp += temp1;

			if (temp2.y < 0)
			{
				temp2 *= -1;
				temp += temp2;
			}
			else
				temp += temp2;

			vertex_buffer_data[x].normal.Set(temp.x / 2, temp.y / 2, temp.z / 2);
		}
		else if (((x + 1) % terrainSize == 0) && x != vertex_buffer_data.size() - 1 && x != terrainSize - 1) //special case for last vertices of all rows excluding last vert and top right vert
		{
			Vector3 currVert = Vector3(vertex_buffer_data[x].pos.x * terrainScale.x, vertex_buffer_data[x].pos.y * terrainScale.y, vertex_buffer_data[x].pos.z * terrainScale.z);
			Vector3 AdjVert1 = Vector3(vertex_buffer_data[x - terrainSize].pos.x * terrainScale.x, vertex_buffer_data[x - terrainSize].pos.y * terrainScale.y, vertex_buffer_data[x - terrainSize].pos.z * terrainScale.z);
			Vector3 AdjVert2 = Vector3(vertex_buffer_data[x + terrainSize].pos.x * terrainScale.x, vertex_buffer_data[x + terrainSize].pos.y * terrainScale.y, vertex_buffer_data[x + terrainSize].pos.z * terrainScale.z);
			Vector3 AdjVert3 = Vector3(vertex_buffer_data[x - 1].pos.x * terrainScale.x, vertex_buffer_data[x - 1].pos.y * terrainScale.y, vertex_buffer_data[x - 1].pos.z * terrainScale.z); //left vert

			Vector3 Vec1 = AdjVert1 - currVert;
			Vector3 Vec2 = AdjVert2 - currVert;
			Vector3 Vec3 = AdjVert3 - currVert; //left vect

			Vector3 temp = Vector3(0, 0, 0);
			Vector3 temp1 = Vec1.Cross(Vec3);
			Vector3 temp2 = Vec2.Cross(Vec3);

			if (temp1.y < 0)
			{
				temp1 *= -1;
				temp += temp1;
			}
			else
				temp += temp1;

			if (temp2.y < 0)
			{
				temp2 *= -1;
				temp += temp2;
			}
			else
				temp += temp2;

			vertex_buffer_data[x].normal.Set(temp.x / 2, temp.y / 2, temp.z / 2);
		}
		else if (x < terrainSize && x != 0 && x != terrainSize - 1) //special case for all verts in first row excluding first vert and top right vert
		{
			Vector3 currVert = Vector3(vertex_buffer_data[x].pos.x * terrainScale.x, vertex_buffer_data[x].pos.y * terrainScale.y, vertex_buffer_data[x].pos.z * terrainScale.z);
			Vector3 AdjVert1 = Vector3(vertex_buffer_data[x + 1].pos.x * terrainScale.x, vertex_buffer_data[x + 1].pos.y * terrainScale.y, vertex_buffer_data[x + 1].pos.z * terrainScale.z);
			Vector3 AdjVert2 = Vector3(vertex_buffer_data[x - 1].pos.x * terrainScale.x, vertex_buffer_data[x - 1].pos.y * terrainScale.y, vertex_buffer_data[x - 1].pos.z * terrainScale.z);
			Vector3 AdjVert3 = Vector3(vertex_buffer_data[x + terrainSize].pos.x * terrainScale.x, vertex_buffer_data[x + terrainSize].pos.y * terrainScale.y, vertex_buffer_data[x + terrainSize].pos.z * terrainScale.z);

			Vector3 Vec1 = AdjVert1 - currVert;
			Vector3 Vec2 = AdjVert2 - currVert;
			Vector3 Vec3 = AdjVert3 - currVert; //left vect

			Vector3 temp = Vector3(0, 0, 0);
			Vector3 temp1 = Vec1.Cross(Vec3);
			Vector3 temp2 = Vec2.Cross(Vec3);

			if (temp1.y < 0)
			{
				temp1 *= -1;
				temp += temp1;
			}
			else
				temp += temp1;

			if (temp2.y < 0)
			{
				temp2 *= -1;
				temp += temp2;
			}
			else
				temp += temp2;

			vertex_buffer_data[x].normal.Set(temp.x / 2, temp.y / 2, temp.z / 2);
		}
		else if (x > vertex_buffer_data.size() - (terrainSize + 1) && x != vertex_buffer_data.size() - 1 && x != (vertex_buffer_data.size() - terrainSize)) // special case for all verts in last row excluding last vert and bottom left vert
		{
			Vector3 currVert = Vector3(vertex_buffer_data[x].pos.x * terrainScale.x, vertex_buffer_data[x].pos.y * terrainScale.y, vertex_buffer_data[x].pos.z * terrainScale.z);
			Vector3 AdjVert1 = Vector3(vertex_buffer_data[x + 1].pos.x * terrainScale.x, vertex_buffer_data[x + 1].pos.y * terrainScale.y, vertex_buffer_data[x + 1].pos.z * terrainScale.z);
			Vector3 AdjVert2 = Vector3(vertex_buffer_data[x - 1].pos.x * terrainScale.x, vertex_buffer_data[x - 1].pos.y * terrainScale.y, vertex_buffer_data[x - 1].pos.z * terrainScale.z);
			Vector3 AdjVert3 = Vector3(vertex_buffer_data[x - terrainSize].pos.x * terrainScale.x, vertex_buffer_data[x - terrainSize].pos.y * terrainScale.y, vertex_buffer_data[x - terrainSize].pos.z * terrainScale.z);

			Vector3 Vec1 = AdjVert1 - currVert;
			Vector3 Vec2 = AdjVert2 - currVert;
			Vector3 Vec3 = AdjVert3 - currVert; //left vect

			Vector3 temp = Vector3(0, 0, 0);
			Vector3 temp1 = Vec1.Cross(Vec3);
			Vector3 temp2 = Vec2.Cross(Vec3);

			if (temp1.y < 0)
			{
				temp1 *= -1;
				temp += temp1;
			}
			else
				temp += temp1;

			if (temp2.y < 0)
			{
				temp2 *= -1;
				temp += temp2;
			}
			else
				temp += temp2;

			vertex_buffer_data[x].normal.Set(temp.x / 2, temp.y / 2, temp.z / 2);
		}
		else //for all vertices in between
		{
			Vector3 currVert = Vector3(vertex_buffer_data[x].pos.x * terrainScale.x, vertex_buffer_data[x].pos.y * terrainScale.y, vertex_buffer_data[x].pos.z * terrainScale.z);
			Vector3 AdjVert1 = Vector3(vertex_buffer_data[x + 1].pos.x * terrainScale.x, vertex_buffer_data[x + 1].pos.y * terrainScale.y, vertex_buffer_data[x + 1].pos.z * terrainScale.z); //right
			Vector3 AdjVert2 = Vector3(vertex_buffer_data[x - 1].pos.x * terrainScale.x, vertex_buffer_data[x - 1].pos.y * terrainScale.y, vertex_buffer_data[x - 1].pos.z * terrainScale.z); //left
			Vector3 AdjVert3 = Vector3(vertex_buffer_data[x - terrainSize].pos.x * terrainScale.x, vertex_buffer_data[x - terrainSize].pos.y * terrainScale.y, vertex_buffer_data[x - terrainSize].pos.z * terrainScale.z); //up
			Vector3 AdjVert4 = Vector3(vertex_buffer_data[x + terrainSize].pos.x * terrainScale.x, vertex_buffer_data[x + terrainSize].pos.y * terrainScale.y, vertex_buffer_data[x + terrainSize].pos.z * terrainScale.z); //down

			Vector3 Vec1 = AdjVert1 - currVert;
			Vector3 Vec2 = AdjVert2 - currVert;
			Vector3 Vec3 = AdjVert3 - currVert;
			Vector3 Vec4 = AdjVert4 - currVert;

			Vector3 temp = Vector3(0, 0, 0);
			Vector3 temp1 = Vec1.Cross(Vec3); //cross up and right
			Vector3 temp2 = Vec1.Cross(Vec4); //cross down and right
			Vector3 temp3 = Vec2.Cross(Vec3); //cross up and left
			Vector3 temp4 = Vec2.Cross(Vec4); //cross down and left

			if (temp1.y < 0)
			{
				temp1 *= -1;
				temp += temp1;
			}
			else
				temp += temp1;

			if (temp2.y < 0)
			{
				temp2 *= -1;
				temp += temp2;
			}
			else
				temp += temp2;

			if (temp3.y < 0)
			{
				temp3 *= -1;
				temp += temp3;
			}
			else
				temp += temp3;

			if (temp4.y < 0)
			{
				temp4 *= -1;
				temp += temp4;
			}
			else
				temp += temp4;

			vertex_buffer_data[x].normal.Set(temp.x / 4, temp.y / 4, temp.z / 4);
		}
	}

	Mesh *mesh = new Mesh(meshName);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLES;

	return mesh;
}
Mesh* MeshBuilder::GenerateTerrainTerrace(const std::string &meshName, std::string file_path, std::vector<unsigned char> &heightMap, Vector3 terrainScale)
{
	file_path = Resources::Path::HeightMap + file_path + ".raw";
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	const float SCALE_FACTOR = 256.f;
	if (!LoadHeightMap(file_path.c_str(), heightMap))
		return NULL;

	unsigned terrainSize = (unsigned)sqrt((double)heightMap.size());

	Mtx44 scale;
	scale.SetToScale(terrainScale.x, terrainScale.y, terrainScale.z);
	for (unsigned z = 0; z < terrainSize; ++z)
	{
		for (unsigned x = 0; x < terrainSize; ++x)
		{
			float scaledHeight = (float)heightMap[z * terrainSize + x] / SCALE_FACTOR;
			v.pos.Set(static_cast<float>(x) / terrainSize - 0.5f, scaledHeight, static_cast<float>(z) / terrainSize - 0.5f);
			Vector3 vPos = { v.pos.x, v.pos.y,v.pos.z };
			vPos.y -= 0.4f; // offset so that mid gray is at 0
			vPos = scale * vPos;
			// round value
			int multiple = 5;
			vPos.y = roundf(vPos.y);
			vPos.y = vPos.y - ((int)vPos.y % multiple);
			v.pos.Set(vPos.x, vPos.y, vPos.z);
			v.color.Set(scaledHeight, scaledHeight, scaledHeight);
			v.normal.Set(0, 1, 0);
			v.texCoord.Set((float)x / terrainSize * 8, 1.f - (float)z / terrainSize * 8);
			vertex_buffer_data.push_back(v);
		}
	}

	for (unsigned z = 0; z < terrainSize - 1; ++z)
	{
		for (unsigned x = 0; x < terrainSize - 1; ++x)
		{
			index_buffer_data.push_back(terrainSize * z + x + 0);
			index_buffer_data.push_back(terrainSize * (z + 1) + x + 0);
			index_buffer_data.push_back(terrainSize * z + x + 1);

			index_buffer_data.push_back(terrainSize * (z + 1) + x + 1);
			index_buffer_data.push_back(terrainSize * z + x + 1);
			index_buffer_data.push_back(terrainSize * (z + 1) + x + 0);
		}
	}
	terrainScale.y = terrainScale.y / (terrainScale.x / terrainScale.y);

	// Normals
	for (unsigned int x = 0; x < vertex_buffer_data.size(); ++x)
	{
		if (x == 0) //for very first vert only
		{
			Vector3 AdjVert1 = Vector3(vertex_buffer_data[x + 1].pos.x * terrainScale.x, vertex_buffer_data[x + 1].pos.y * terrainScale.y, vertex_buffer_data[x + 1].pos.z * terrainScale.z);
			Vector3 currVert = Vector3(vertex_buffer_data[x].pos.x * terrainScale.x, vertex_buffer_data[x].pos.y * terrainScale.y, vertex_buffer_data[x].pos.z * terrainScale.z);
			Vector3 Vec1 = AdjVert1 - currVert;

			Vector3 AdjVert2 = Vector3(vertex_buffer_data[x + terrainSize].pos.x * terrainScale.x, vertex_buffer_data[x + terrainSize].pos.y * terrainScale.y, vertex_buffer_data[x + terrainSize].pos.z * terrainScale.z);
			Vector3 Vec2 = AdjVert2 - currVert;

			Vector3 temp = Vec1.Cross(Vec2);
			if (temp.y < 0)
				temp *= -1;
			vertex_buffer_data[x].normal.Set(temp.x, temp.y, temp.z);
		}
		else if (x == (terrainSize - 1)) //top rightt corner vert special case
		{
			Vector3 AdjVert1 = Vector3(vertex_buffer_data[x - 1].pos.x * terrainScale.x, vertex_buffer_data[x - 1].pos.y * terrainScale.y, vertex_buffer_data[x - 1].pos.z * terrainScale.z);
			Vector3 currVert = Vector3(vertex_buffer_data[x].pos.x * terrainScale.x, vertex_buffer_data[x].pos.y * terrainScale.y, vertex_buffer_data[x].pos.z * terrainScale.z);
			Vector3 Vec1 = AdjVert1 - currVert;

			Vector3 AdjVert2 = Vector3(vertex_buffer_data[x + terrainSize].pos.x * terrainScale.x, vertex_buffer_data[x + terrainSize].pos.y * terrainScale.y, vertex_buffer_data[x + terrainSize].pos.z * terrainScale.z);
			Vector3 Vec2 = AdjVert2 - currVert;

			Vector3 temp = Vec1.Cross(Vec2);
			if (temp.y < 0)
				temp *= -1;

			vertex_buffer_data[x].normal.Set(temp.x, temp.y, temp.z);
		}
		else if (x == (vertex_buffer_data.size() - terrainSize)) //bottom left corner vert special case
		{
			Vector3 AdjVert1 = Vector3(vertex_buffer_data[x + 1].pos.x * terrainScale.x, vertex_buffer_data[x + 1].pos.y * terrainScale.y, vertex_buffer_data[x + 1].pos.z * terrainScale.z);
			Vector3 currVert = Vector3(vertex_buffer_data[x].pos.x * terrainScale.x, vertex_buffer_data[x].pos.y * terrainScale.y, vertex_buffer_data[x].pos.z * terrainScale.z);
			Vector3 Vec1 = AdjVert1 - currVert;

			Vector3 AdjVert2 = Vector3(vertex_buffer_data[x - terrainSize].pos.x * terrainScale.x, vertex_buffer_data[x - terrainSize].pos.y * terrainScale.y, vertex_buffer_data[x - terrainSize].pos.z * terrainScale.z);
			Vector3 Vec2 = AdjVert2 - currVert;

			Vector3 temp = Vec1.Cross(Vec2);
			if (temp.y < 0)
				temp *= -1;

			vertex_buffer_data[x].normal.Set(temp.x, temp.y, temp.z);
		}
		else if (x == vertex_buffer_data.size() - 1) //For bottom right last vert special case
		{
			Vector3 AdjVert1 = Vector3(vertex_buffer_data[x - 1].pos.x * terrainScale.x, vertex_buffer_data[x - 1].pos.y * terrainScale.y, vertex_buffer_data[x - 1].pos.z * terrainScale.z);
			Vector3 currVert = Vector3(vertex_buffer_data[x].pos.x * terrainScale.x, vertex_buffer_data[x].pos.y * terrainScale.y, vertex_buffer_data[x].pos.z * terrainScale.z);
			Vector3 Vec1 = AdjVert1 - currVert;

			Vector3 AdjVert2 = Vector3(vertex_buffer_data[x - terrainSize].pos.x * terrainScale.x, vertex_buffer_data[x - terrainSize].pos.y * terrainScale.y, vertex_buffer_data[x - terrainSize].pos.z * terrainScale.z);
			Vector3 Vec2 = AdjVert2 - currVert;

			Vector3 temp = Vec1.Cross(Vec2);
			if (temp.y < 0)
				temp *= -1;
			vertex_buffer_data[x].normal.Set(temp.x, temp.y, temp.z);
		}
		else if ((x % terrainSize) == 0 && x != 0 && x != (vertex_buffer_data.size() - terrainSize)) //special case for first vertices of all rows excluding first vert and bottom left vert
		{
			Vector3 currVert = Vector3(vertex_buffer_data[x].pos.x * terrainScale.x, vertex_buffer_data[x].pos.y * terrainScale.y, vertex_buffer_data[x].pos.z * terrainScale.z);
			Vector3 AdjVert1 = Vector3(vertex_buffer_data[x - terrainSize].pos.x * terrainScale.x, vertex_buffer_data[x - terrainSize].pos.y * terrainScale.y, vertex_buffer_data[x - terrainSize].pos.z * terrainScale.z);
			Vector3 AdjVert2 = Vector3(vertex_buffer_data[x + terrainSize].pos.x * terrainScale.x, vertex_buffer_data[x + terrainSize].pos.y * terrainScale.y, vertex_buffer_data[x + terrainSize].pos.z * terrainScale.z);
			Vector3 AdjVert3 = Vector3(vertex_buffer_data[x + 1].pos.x * terrainScale.x, vertex_buffer_data[x + 1].pos.y * terrainScale.y, vertex_buffer_data[x + 1].pos.z * terrainScale.z); //right vert

			Vector3 Vec1 = AdjVert1 - currVert;
			Vector3 Vec2 = AdjVert2 - currVert;
			Vector3 Vec3 = AdjVert3 - currVert; //right vect

			Vector3 temp = Vector3(0, 0, 0);
			Vector3 temp1 = Vec1.Cross(Vec3);
			Vector3 temp2 = Vec2.Cross(Vec3);

			if (temp1.y < 0)
			{
				temp1 *= -1;
				temp += temp1;
			}
			else
				temp += temp1;

			if (temp2.y < 0)
			{
				temp2 *= -1;
				temp += temp2;
			}
			else
				temp += temp2;

			vertex_buffer_data[x].normal.Set(temp.x / 2, temp.y / 2, temp.z / 2);
		}
		else if (((x + 1) % terrainSize == 0) && x != vertex_buffer_data.size() - 1 && x != terrainSize - 1) //special case for last vertices of all rows excluding last vert and top right vert
		{
			Vector3 currVert = Vector3(vertex_buffer_data[x].pos.x * terrainScale.x, vertex_buffer_data[x].pos.y * terrainScale.y, vertex_buffer_data[x].pos.z * terrainScale.z);
			Vector3 AdjVert1 = Vector3(vertex_buffer_data[x - terrainSize].pos.x * terrainScale.x, vertex_buffer_data[x - terrainSize].pos.y * terrainScale.y, vertex_buffer_data[x - terrainSize].pos.z * terrainScale.z);
			Vector3 AdjVert2 = Vector3(vertex_buffer_data[x + terrainSize].pos.x * terrainScale.x, vertex_buffer_data[x + terrainSize].pos.y * terrainScale.y, vertex_buffer_data[x + terrainSize].pos.z * terrainScale.z);
			Vector3 AdjVert3 = Vector3(vertex_buffer_data[x - 1].pos.x * terrainScale.x, vertex_buffer_data[x - 1].pos.y * terrainScale.y, vertex_buffer_data[x - 1].pos.z * terrainScale.z); //left vert

			Vector3 Vec1 = AdjVert1 - currVert;
			Vector3 Vec2 = AdjVert2 - currVert;
			Vector3 Vec3 = AdjVert3 - currVert; //left vect

			Vector3 temp = Vector3(0, 0, 0);
			Vector3 temp1 = Vec1.Cross(Vec3);
			Vector3 temp2 = Vec2.Cross(Vec3);

			if (temp1.y < 0)
			{
				temp1 *= -1;
				temp += temp1;
			}
			else
				temp += temp1;

			if (temp2.y < 0)
			{
				temp2 *= -1;
				temp += temp2;
			}
			else
				temp += temp2;

			vertex_buffer_data[x].normal.Set(temp.x / 2, temp.y / 2, temp.z / 2);
		}
		else if (x < terrainSize && x != 0 && x != terrainSize - 1) //special case for all verts in first row excluding first vert and top right vert
		{
			Vector3 currVert = Vector3(vertex_buffer_data[x].pos.x * terrainScale.x, vertex_buffer_data[x].pos.y * terrainScale.y, vertex_buffer_data[x].pos.z * terrainScale.z);
			Vector3 AdjVert1 = Vector3(vertex_buffer_data[x + 1].pos.x * terrainScale.x, vertex_buffer_data[x + 1].pos.y * terrainScale.y, vertex_buffer_data[x + 1].pos.z * terrainScale.z);
			Vector3 AdjVert2 = Vector3(vertex_buffer_data[x - 1].pos.x * terrainScale.x, vertex_buffer_data[x - 1].pos.y * terrainScale.y, vertex_buffer_data[x - 1].pos.z * terrainScale.z);
			Vector3 AdjVert3 = Vector3(vertex_buffer_data[x + terrainSize].pos.x * terrainScale.x, vertex_buffer_data[x + terrainSize].pos.y * terrainScale.y, vertex_buffer_data[x + terrainSize].pos.z * terrainScale.z);

			Vector3 Vec1 = AdjVert1 - currVert;
			Vector3 Vec2 = AdjVert2 - currVert;
			Vector3 Vec3 = AdjVert3 - currVert; //left vect

			Vector3 temp = Vector3(0, 0, 0);
			Vector3 temp1 = Vec1.Cross(Vec3);
			Vector3 temp2 = Vec2.Cross(Vec3);

			if (temp1.y < 0)
			{
				temp1 *= -1;
				temp += temp1;
			}
			else
				temp += temp1;

			if (temp2.y < 0)
			{
				temp2 *= -1;
				temp += temp2;
			}
			else
				temp += temp2;

			vertex_buffer_data[x].normal.Set(temp.x / 2, temp.y / 2, temp.z / 2);
		}
		else if (x > vertex_buffer_data.size() - (terrainSize + 1) && x != vertex_buffer_data.size() - 1 && x != (vertex_buffer_data.size() - terrainSize)) // special case for all verts in last row excluding last vert and bottom left vert
		{
			Vector3 currVert = Vector3(vertex_buffer_data[x].pos.x * terrainScale.x, vertex_buffer_data[x].pos.y * terrainScale.y, vertex_buffer_data[x].pos.z * terrainScale.z);
			Vector3 AdjVert1 = Vector3(vertex_buffer_data[x + 1].pos.x * terrainScale.x, vertex_buffer_data[x + 1].pos.y * terrainScale.y, vertex_buffer_data[x + 1].pos.z * terrainScale.z);
			Vector3 AdjVert2 = Vector3(vertex_buffer_data[x - 1].pos.x * terrainScale.x, vertex_buffer_data[x - 1].pos.y * terrainScale.y, vertex_buffer_data[x - 1].pos.z * terrainScale.z);
			Vector3 AdjVert3 = Vector3(vertex_buffer_data[x - terrainSize].pos.x * terrainScale.x, vertex_buffer_data[x - terrainSize].pos.y * terrainScale.y, vertex_buffer_data[x - terrainSize].pos.z * terrainScale.z);

			Vector3 Vec1 = AdjVert1 - currVert;
			Vector3 Vec2 = AdjVert2 - currVert;
			Vector3 Vec3 = AdjVert3 - currVert; //left vect

			Vector3 temp = Vector3(0, 0, 0);
			Vector3 temp1 = Vec1.Cross(Vec3);
			Vector3 temp2 = Vec2.Cross(Vec3);

			if (temp1.y < 0)
			{
				temp1 *= -1;
				temp += temp1;
			}
			else
				temp += temp1;

			if (temp2.y < 0)
			{
				temp2 *= -1;
				temp += temp2;
			}
			else
				temp += temp2;

			vertex_buffer_data[x].normal.Set(temp.x / 2, temp.y / 2, temp.z / 2);
		}
		else //for all vertices in between
		{
			Vector3 currVert = Vector3(vertex_buffer_data[x].pos.x * terrainScale.x, vertex_buffer_data[x].pos.y * terrainScale.y, vertex_buffer_data[x].pos.z * terrainScale.z);
			Vector3 AdjVert1 = Vector3(vertex_buffer_data[x + 1].pos.x * terrainScale.x, vertex_buffer_data[x + 1].pos.y * terrainScale.y, vertex_buffer_data[x + 1].pos.z * terrainScale.z); //right
			Vector3 AdjVert2 = Vector3(vertex_buffer_data[x - 1].pos.x * terrainScale.x, vertex_buffer_data[x - 1].pos.y * terrainScale.y, vertex_buffer_data[x - 1].pos.z * terrainScale.z); //left
			Vector3 AdjVert3 = Vector3(vertex_buffer_data[x - terrainSize].pos.x * terrainScale.x, vertex_buffer_data[x - terrainSize].pos.y * terrainScale.y, vertex_buffer_data[x - terrainSize].pos.z * terrainScale.z); //up
			Vector3 AdjVert4 = Vector3(vertex_buffer_data[x + terrainSize].pos.x * terrainScale.x, vertex_buffer_data[x + terrainSize].pos.y * terrainScale.y, vertex_buffer_data[x + terrainSize].pos.z * terrainScale.z); //down

			Vector3 Vec1 = AdjVert1 - currVert;
			Vector3 Vec2 = AdjVert2 - currVert;
			Vector3 Vec3 = AdjVert3 - currVert;
			Vector3 Vec4 = AdjVert4 - currVert;

			Vector3 temp = Vector3(0, 0, 0);
			Vector3 temp1 = Vec1.Cross(Vec3); //cross up and right
			Vector3 temp2 = Vec1.Cross(Vec4); //cross down and right
			Vector3 temp3 = Vec2.Cross(Vec3); //cross up and left
			Vector3 temp4 = Vec2.Cross(Vec4); //cross down and left

			if (temp1.y < 0)
			{
				temp1 *= -1;
				temp += temp1;
			}
			else
				temp += temp1;

			if (temp2.y < 0)
			{
				temp2 *= -1;
				temp += temp2;
			}
			else
				temp += temp2;

			if (temp3.y < 0)
			{
				temp3 *= -1;
				temp += temp3;
			}
			else
				temp += temp3;

			if (temp4.y < 0)
			{
				temp4 *= -1;
				temp += temp4;
			}
			else
				temp += temp4;

			vertex_buffer_data[x].normal.Set(temp.x / 4, temp.y / 4, temp.z / 4);
		}
	}

	Mesh *mesh = new Mesh(meshName);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLES;

	return mesh;
}
Mesh* MeshBuilder::GenerateSkyPlane(const std::string &meshName, Color color, int slices, float PlanetRadius, float AtmosphereRadius, float hTile, float vTile)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	// To ensure no of slices is between 1 - 256
	slices = Math::Clamp(slices, 1, 256);

	// Calculate some values we will need
	float planeSize = 2.0f * (float)sqrtf((AtmosphereRadius*AtmosphereRadius) + (PlanetRadius*PlanetRadius));

	float delta = planeSize / (float)slices; //Divide plane evenly

	// Calculate texture coordinate as per slice. Using 2.0f to divide or 1.0f to divide is a factor for us to use further for purpose of tiling when possible. (Tiling meant to duplicate a texture image multiple times over a mesh.)
	float texDelta = 2.0f / (float)slices;

	// Calculate x and z vertices
	for (int z = 0; z <= slices; ++z)
	{
		for (int x = 0; x <= slices; ++x)
		{
			float xDist = (-0.5f * planeSize) + ((float)x * delta);
			float zDist = (-0.5f * planeSize) + ((float)z * delta);

			// Divide by AtmosphereRadius is to normalize height value for use in your scene.
			// With reference to a parabola curve, we use quadratics y = xsquare
			float xHeight = (xDist * xDist) / AtmosphereRadius;
			float zHeight = (zDist * zDist) / AtmosphereRadius;
			float height = xHeight + zHeight;

			// Assign position for x, y, z.
			// y is -height to get an inverted U shape of a parabola curve shape.
			v.pos.x = xDist;
			v.pos.y = 0.0f - height;
			v.pos.z = zDist;

			// Calculate the texture coordinates
			v.texCoord.u = hTile * ((float)x * texDelta * 0.5f);
			v.texCoord.v = vTile * (1.0f - (float)z * texDelta * 0.5f);

			v.color = color;

			vertex_buffer_data.push_back(v);
		}
	}

	// Calculate the indices
	int index = 0;	// Indices
	for (int i = 0; i < slices; ++i)
	{
		for (int j = 0; j < slices; ++j)
		{
			// To understand further, try to use numbers to test. Check lesson slides.
			// There are various way to plot indices.
			int startvert = (i * (slices + 1) + j);
			index_buffer_data.push_back(startvert);			// tri 1   (0)
			index_buffer_data.push_back(startvert + 1);				// (1)
			index_buffer_data.push_back(startvert + slices + 1);	// (2)

			index_buffer_data.push_back(startvert + 1); 	// tri 2   (3)
			index_buffer_data.push_back(startvert + slices + 2);	// (2)
			index_buffer_data.push_back(startvert + slices + 1);	// (1)
		}
	}

	Mesh *mesh = new Mesh(meshName);

	mesh->mode = Mesh::DRAW_TRIANGLES;

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();

	return mesh;
}
AnimatedMesh* MeshBuilder::GenerateAnimatedMesh(std::string sMeshName, int numRow, int numCol, int start, int end, float time, bool loop)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	float width = 1.f / numCol;
	float height = 1.f / numRow;
	int offset = 0;

	for (int i = 0; i < numRow; ++i)
	{
		for (int j = 0; j < numCol; ++j)
		{
			float u1 = j * width;
			float v1 = 1.f - height - i * height;

			v.pos = { -0.5f, -0.5f, 0.0f }; //top left
			v.texCoord.Set(u1, v1);
			vertex_buffer_data.push_back(v);

			v.pos = { 0.5f, -0.5f, 0.0f }; //top right
			v.texCoord.Set(u1 + width, v1);
			vertex_buffer_data.push_back(v);

			v.pos = { 0.5f, 0.5f, 0.0f }; //bottom left
			v.texCoord.Set(u1 + width, v1 + height);
			vertex_buffer_data.push_back(v);

			v.pos = { -0.5f, 0.5f, 0.0f }; //bottom right
			v.texCoord.Set(u1, v1 + height);
			vertex_buffer_data.push_back(v);

			index_buffer_data.push_back(offset + 0);
			index_buffer_data.push_back(offset + 1);
			index_buffer_data.push_back(offset + 2);
			index_buffer_data.push_back(offset + 0);
			index_buffer_data.push_back(offset + 2);
			index_buffer_data.push_back(offset + 3);
			offset += 4;
		}
	}

	Mesh* mesh = new Mesh(sMeshName);

	mesh->mode = Mesh::DRAW_TRIANGLES;

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	AnimatedMesh *anim = new AnimatedMesh(sMeshName, numRow, numCol, start, end, time, loop, mesh);
	return anim;
}