#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include <string>
#include <glad/glad.h>
#include <vector>


enum ProgramType
{
	VERTEX_PROGRAM,
	FRAGMENT_PROGRAM,
	UNKNOWN
};

class ShaderObject
{
public:
	ShaderObject(const std::string& path, GLenum type);
	void print_shader_error();

	ProgramType type;
	GLuint id;

private:

};

class Program
{
public:
	Program() = delete;
	Program(const ShaderObject& vertex_program, const ShaderObject& fragment_program);

	void use_program() const;

	void set_uniform_float(const GLchar* name, const float& val);
	void set_uniform_unsigned_int(const GLchar* name, const unsigned int& val);
	void set_uniform_matrix(const GLchar* name, const GLfloat* val);
	void set_uniform_vec3(const GLchar* name, const GLfloat* val);
	void set_uniform_light(const Light& light);

private:
	bool print_program_error() const;

	GLuint id;
	std::vector<ShaderObject> shader_stages;
};

// TODO implement uniform dictionary to avoid glGetUniformLocation every time

#endif // SHADER_PROGRAM_H