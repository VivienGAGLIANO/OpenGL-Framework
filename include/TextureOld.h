#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>


class TextureOld
{
public:
	explicit TextureOld(const char* image_path);

private:
	GLuint id;

	static GLuint load_bmp(const char* image_path);
};

#endif