#ifndef MATERIAL_H
#define MATERIAL_H
#include "Resources.h"
#define DEFAULT_DIFFUSE Resources::Defaults::fDiffuse
#define DEFAULT_AMBIENT  Resources::Defaults::fAmbient
#define DEFAULT_SPECULAR  Resources::Defaults::fSpecular
#define DEFAULT_SHININESS Resources::Defaults::fShininess

struct Comp
{
	float r, g, b;
	Comp() {};
	Comp(float r, float g, float b) { Set(r, g, b); }
	void Set(float r, float g, float b) { this->r = r; this->g = g; this->b = b; }
};
struct Material
{
	Comp kAmbient;
	Comp kDiffuse;
	Comp kSpecular;
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