#ifndef PIPELINE_H
#define PIPELINE_H

#include <glad/glad.h>
#include <string>


class Pipeline
{
public:
	Pipeline(const std::string &vertex_path, const std::string &fragment_path);

	void use_pipeline() const;
	void set_uniform_float(GLuint program, const GLchar* name, const float &val);
	void set_uniform_matrix(GLuint program, const GLchar *name, const GLfloat *val);
	void set_uniform_vec3(GLuint program, const GLchar* name, const GLfloat* val);

	GLuint get_vertex_id() const;
	GLuint get_fragment_id() const;
	GLuint get_pipeline_id() const;

private:
	GLuint pipeline, vertex, fragment;

	static GLuint create_shader_program(const std::string& path, GLenum type);
	static void print_program_error(GLuint program);
	static void print_pipeline_error(GLuint pipeline);
};


#endif
