#include <fstream>
#include <gtc/type_ptr.hpp>
#include <iostream>
#include <set>
#include <sstream>
#include <vector>

#include "light.h"
#include "shader_program.h"

/************************************** Shader Program **************************************/

ShaderObject::ShaderObject(const std::string& path, GLenum type)
{
	// TODO error here in shader program creation
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

	const GLchar* code_str = (const GLchar*) code.c_str();

	id = glCreateShader(type);

	glShaderSource(id, 1, &code_str, 0);

	glCompileShader(id);

	print_shader_error();

	this->type = [type]()
	{
		switch (type)
		{
		case GL_VERTEX_SHADER: return VERTEX_PROGRAM;
		case GL_FRAGMENT_SHADER: return FRAGMENT_PROGRAM;
		default: return UNKNOWN;
		}
	}();
}

void ShaderObject::print_shader_error()
{
	GLint is_compiled = 0;
	glGetShaderiv(id, GL_COMPILE_STATUS, &is_compiled);
	if (is_compiled == GL_FALSE)
	{
		GLint max_length = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &max_length);

		// The max_length includes the NULL character
		std::vector<GLchar> info_log(max_length);
		glGetShaderInfoLog(id, max_length, &max_length, &info_log[0]);

		// Provide the infolog in whatever manor you deem best.
		for (auto c : info_log)
		{
			std::cout << c;
		}
		std::cout << std::endl;

		// Exit with failure.
		glDeleteShader(id); // Don't leak the shader.
		return;
	}
}


/************************************** Program Object **************************************/

Program::Program(const ShaderObject& vertex_program, const ShaderObject& fragment_program)
	: shader_stages({vertex_program, fragment_program})
{
	id = glCreateProgram();

	// Check for duplicate shader stage
	struct ShaderStageComparator 
	{
		bool operator()(const ShaderObject& a, const ShaderObject& b) const
		{
			return a.type < b.type;
		}
	};
	std::set < ShaderObject, ShaderStageComparator > unique_type(shader_stages.cbegin(), shader_stages.cend());
	if (unique_type.size() != shader_stages.size())
	{
		std::cout << "Program " << id << " warning : multiple shaders attached to same stage. \n";
	}

	// Attach shader programs
	for (auto shader : shader_stages)
	{
		glAttachShader(id, shader.id);
	}

	// Pre-link set up. Cannot be changed after link. See https://www.khronos.org/opengl/wiki/Shader_Compilation#Program_setup for mor details.
	// Vertex shader input attribute locations.
	// Fragment shader output color numbers.
	// Transform feedback output capturing.
	// Program separation.

	// Link program and check for linking error
	glLinkProgram(id);
	if (!print_program_error())
		return;

	// Clean up
	for (auto shader : shader_stages)
	{
		glDetachShader(id, shader.id);
		glDeleteShader(shader.id);
	}
}

void Program::use_program() const
{
	glUseProgram(id);
}

void Program::set_uniform_float(const GLchar* name, const float& val)
{
	glProgramUniform1f(id, glGetUniformLocation(id, name), val);
}

void Program::set_uniform_unsigned_int(const GLchar* name, const unsigned int& val)
{
	glProgramUniform1ui(id, glGetUniformLocation(id, name), val);
}

void Program::set_uniform_matrix(const GLchar* name, const GLfloat* val)
{
	glProgramUniformMatrix4fv(id, glGetUniformLocation(id, name), 1, GL_FALSE, val);
}

void Program::set_uniform_vec3(const GLchar* name, const GLfloat* val)
{
	glProgramUniform3fv(id, glGetUniformLocation(id, name), 1, val);
}

void Program::set_uniform_light(const Light& light)
{
	set_uniform_vec3("light.position", glm::value_ptr(light.position));

	set_uniform_vec3("light.ambiant", glm::value_ptr(light.ambiant));
	set_uniform_vec3("light.diffuse", glm::value_ptr(light.diffuse));
	set_uniform_vec3("light.specular", glm::value_ptr(light.specular));

	set_uniform_float("light.shininess", light.shininess);
}

bool Program::print_program_error() const
{
	GLint is_linked = 0;
	glGetProgramiv(id, GL_LINK_STATUS, &is_linked);
	if (is_linked == GL_FALSE)
	{
		GLint max_length = 0;
		glGetProgramiv(id, GL_INFO_LOG_LENGTH, &max_length);

		// The max_length includes the NULL character
		std::vector<GLchar> infoLog(max_length);
		glGetProgramInfoLog(id, max_length, &max_length, &infoLog[0]);

		// The program is useless now. So delete it, and all involved shader programs.
		for (auto shader : shader_stages)
		{
			glDeleteShader(shader.id);
		}
		glDeleteProgram(id);

		// Provide the infolog in whatever manner you deem best.
		// Exit with failure.
		return false;
	}

	return true;
}