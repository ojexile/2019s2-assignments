#ifndef COLOR_FBO_H
#define COLOR_FBO_H

#include <GL/glew.h>

class ColorFBO
{
public:
	ColorFBO();
	~ColorFBO();

	bool Init(unsigned width, unsigned height);
	void BindForWriting() const;
	void BindForReading(GLenum textureUnit) const;

	GLuint GetFBO() const { return m_fbo; }
	GLuint GetTexture()const { return m_texture; }
	unsigned GetWidth() const { return m_width; }
	unsigned GetHeight()const { return m_height; }

private:
	GLuint m_fbo;		// The frame buffer object, to be written to
	GLuint m_texture;	// Depth texture, to be sampled later in your shader
	unsigned m_width;
	unsigned m_height;
};

#endif
