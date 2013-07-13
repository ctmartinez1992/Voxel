#pragma once

#include <GL/glew.h>
#include "Bitmap.h"

class Texture {
	/*************** Variables ***************/
private:
	//Acts as a pointer to the actual texture.
	GLuint					_object;

	//Original width and height of the texture.
    GLfloat					_originalWidth;
    GLfloat					_originalHeight;

	/*************** Methods ***************/  
private:
	//Copying disabled.
	Texture(const Texture&);

	//Copying disabled.
    const Texture& operator =(const Texture&);

public:
	Texture(const Bitmap& bitmap, GLint minMagFiler = GL_LINEAR, GLint wrapMode = GL_CLAMP_TO_EDGE);
    ~Texture();

	GLuint					object() const;
    GLfloat					originalWidth() const;
	GLfloat					originalHeight() const;
};
