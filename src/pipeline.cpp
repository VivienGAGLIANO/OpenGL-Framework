#include <iostream>
#include "pipeline.h"

#include <fstream>
#include <sstream>
#include <vector>
//#include <gtc/type_ptr.inl>


Pipeline::Pipeline(const std::string &vertex_path, const std::string &fragment_path)
	: vertex(create_shader_program(vertex_path, GL_VERTEX_SHADER)),
	  fragment(create_shader_program(fragment_path, GL_FRAGMENT_SHADER))
{
	print_program_error(vertex);
	print_program_error(fragment);

	glCreateProgramPipelines(1, &pipeline);
	glUseProgramStages(pipeline, GL_VERTEX_SHADER_BIT, vertex);
	glUseProgramStages(pipeline, GL_FRAGMENT_SHADER_BIT, fragment);

	glValidateProgramPipeline(pipeline);
	print_pipeline_error(pipeline);

	if (glGetError() != GL_NO_ERROR) {
		std::cerr << "OpenGL error" << std::endl;
		pipeline = NULL;
	}
}

void Pipeline::use_pipeline() const
{
	glBindProgramPipeline(pipeline);
}

void Pipeline::set_uniform_float(GLuint program, const GLchar *name, const float& val)
{
	glProgramUniform1f(program, glGetUniformLocation(program, name), val);
}

void Pipeline::set_uniform_matrix(GLuint program, const GLchar* name, const GLfloat *val)
{
	glProgramUniformMatrix4fv(program, glGetUniformLocation(program, name), 1, GL_FALSE, val);
}

void Pipeline::set_uniform_vec3(GLuint program, const GLchar* name, const GLfloat* val)
{
	glProgramUniform3fv(program, glGetUniformLocation(program, name), 3, val);
}

GLuint Pipeline::get_vertex_id() const
{
	return vertex;
}

GLuint Pipeline::get_fragment_id() const
{
	return fragment;
}

GLuint Pipeline::get_pipeline_id() const
{
	return pipeline;
}

GLuint Pipeline::create_shader_program(const std::string& path, GLenum type)
{
	std::string code;
	std::ifstream stream(path, std::ios::in);
	if (stream.is_open())
	{
		std::stringstream sstr;
		sstr << stream.rdbuf();
		code = sstr.str();
		stream.close();
	}
	else
	{
		std::cerr << "Unable to open " + path << std::endl;
	}

	const char *pointer = code.c_str();

	// const GLchar*pointer = "#version 460 core layout(location = 0) in vec3 position;layout(location = 1) in vec3 color;layout(location = 2) in vec3 normal;layout(location = 3) in vec2 uv_coord;uniform mat4 m, v, p;out VTF{vec3 v_color;	vec3 v_normal;vec2 v_coord;vec3 world_pos;};out gl_PerVertex{vec4 gl_Position;};void main(){gl_Position = p * v * m * vec4(position, 1.0);v_color = color;v_normal = normal;v_coord = uv_coord;	world_pos = (m * vec4(position, 1.0)).xyz;}";


	return glCreateShaderProgramv(type, 1, &pointer);
}

void Pipeline::print_program_error(GLuint program)
{
	GLuint isLinked;
	glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);
		// The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

		std::cout << "Error : " + std::string(infoLog.begin(), infoLog.end()) + "\n";

		// We don't need the program anymore.
		glDeleteProgram(program);
		return;
	}
}

void Pipeline::print_pipeline_error(GLuint pipeline)
{
	GLuint isValid;
	glGetProgramPipelineiv(pipeline, GL_VALIDATE_STATUS, (int*)&isValid);
	if (isValid == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramPipelineiv(pipeline, GL_INFO_LOG_LENGTH, &maxLength);
		// The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetProgramPipelineInfoLog(pipeline, maxLength, &maxLength, &infoLog[0]);

		std::cout << "Error : " + std::string(infoLog.begin(), infoLog.end()) + "\n";
		// We don't need the program anymore.
		glDeleteProgram(pipeline);
		return;
	}
}
