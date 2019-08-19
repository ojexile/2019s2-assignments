#ifndef MATERIAL_H
#define MATERIAL_H
#include "Resources.h"
#include "Vertex.h"
#define DEFAULT_DIFFUSE Resources::Defaults::fDiffuse
#define DEFAULT_AMBIENT  Resources::Defaults::fAmbient
#define DEFAULT_SPECULAR  Resources::Defaults::fSpecular
#define DEFAULT_SHININESS Resources::Defaults::fShininess

struct Component
{
	float r, g, b;
	Component() {};
	Component(float r, float g, float b) { Set(r, g, b); }
	void Set(float r, float g, float b) { this->r = r; this->g = g; this->b = b; }
};
struct Material
{
	Color kAmbient;
	Color kDiffuse;
	Color kSpecular;
	float kShininess;

	Material()
	{
		//some default values
		kAmbient.Set(DEFAULT_AMBIENT, DEFAULT_AMBIENT, DEFAULT_AMBIENT);
		kDiffuse.Set(DEFAULT_DIFFUSE, DEFAULT_DIFFUSE, DEFAULT_DIFFUSE);
		kSpecular.Set(DEFAULT_SPECULAR, DEFAULT_SPECULAR, DEFAULT_SPECULAR);
		kShininess = DEFAULT_SHININESS;
	}
	void Reset()
	{
		kAmbient.Set(DEFAULT_AMBIENT, DEFAULT_AMBIENT, DEFAULT_AMBIENT);
		kDiffuse.Set(DEFAULT_DIFFUSE, DEFAULT_DIFFUSE, DEFAULT_DIFFUSE);
		kSpecular.Set(DEFAULT_SPECULAR, DEFAULT_SPECULAR, DEFAULT_SPECULAR);
		kShininess = DEFAULT_SHININESS;
	}
};

#endif