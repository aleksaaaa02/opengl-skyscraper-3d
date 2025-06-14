#include "shader.h"
#include <iostream>

void Shader::use()
{
	glUseProgram(ID);
}

void Shader::setBool(const std::string &name, bool value)
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);	
}

void Shader::setInt(const std::string &name, int value)
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);	
}

void Shader::setMat4(const std::string &name, const glm::mat4 value)
{
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &value[0][0]);
}

void Shader::setVec3(const std::string &name, float x, float y, float z)
{
	glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
}

void Shader::setVec3(const std::string &name, glm::vec3 value)
{
	glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::setVec4(const std::string &name, glm::vec4 value)
{
	glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::setFloat(const std::string &name, float value)
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

Shader::Shader(const char* vertexPath, const char* fragPath)
{
	unsigned int program;
	unsigned int vertexShader;
	unsigned int fragmentShader;
	
	program = glCreateProgram();

	vertexShader = compileShader(GL_VERTEX_SHADER, vertexPath);
	fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragPath);

	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

	glLinkProgram(program);
	glValidateProgram(program);
	
	int success;
	char infoLog[512];
	glGetProgramiv(program, GL_VALIDATE_STATUS, &success);

	if (success == GL_FALSE) {
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		std::cout << "Error creating shader program: " << std::endl 
			<< infoLog << std::endl;
	}
	
	glDetachShader(program, vertexShader);
	glDeleteShader(vertexShader);
	glDetachShader(program, fragmentShader);
	glDeleteShader(fragmentShader);

	this -> ID = program;
}


Shader::~Shader()
{
	glDeleteProgram(this -> ID);
}

unsigned int Shader::compileShader(GLenum type, const char* source)
{
	std::ifstream file(source);
	std::stringstream ss;

	if (file.is_open())
	{
		ss << file.rdbuf();
		file.close();
		std::cout << "Finished reading the file" << std::endl;
	} else {
		ss << "";
		std::cout << "Failed to read the file" << std::endl;
	}

	std::string tmp = ss.str();
	const char* code = tmp.c_str();

	int shader = glCreateShader(type);

	int success;
	char infoLog[512];

	glShaderSource(shader, 1, &code, NULL);
	glCompileShader(shader);

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (success == GL_FALSE) 
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		if (type == GL_VERTEX_SHADER) {
			std::cout << "Vertex ";	
		} else if (type == GL_FRAGMENT_SHADER) {
			std::cout << "Fragment ";	
		} 
		std::cout << "shader has error:" << std::endl;
		std::cout << infoLog << std::endl;

	} 	
	return shader;
}

