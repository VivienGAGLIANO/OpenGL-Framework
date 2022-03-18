#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <glad/glad.h>


class Texture
{
public:
	explicit Texture(const char* image_path);

private:
	GLuint id;

	static GLuint load_bmp(const char* image_path);
};

#endif