#ifndef MATERIAL_H
#define MATERIAL_H

#define DEFAULT_DIFFUSE 0.8f
#define DEFAULT_AMBIENT 0.4f
#define DEFAULT_SPECULAR 0.3f
#define DEFAULT_SHININESS 5.f

struct Component
{
	float r, g, b;
	Component(float r = 0.1f, float g = 0.1f, float b = 0.1f) { Set(r, g, b); }
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
};

#endif