#ifndef MATERIAL_H
#define MATERIAL_H

#define DEFAULT_DIFFUSE 0.8f
#define DEFAULT_AMBIENT 0.5f
#define DEFAULT_SPECULAR 0.1f
#define DEFAULT_SHININESS 1.f

struct Component
{
	float r, g, b;
	Component() {};
	Component(float r, float g, float b) { Set(r, g, b); }
	void Set(float r, float g, float b) { this->r = r; this->g = g; this->b = b; }
};
struct Material
{
	Component kAmbient;
	Component kDiffuse;
	Component kSpecular;
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