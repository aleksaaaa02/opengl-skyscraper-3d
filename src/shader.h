#pragma once
#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>

class Shader {

public:
	unsigned int ID;
	void use();
	void setBool(const std::string &name, bool value);
	void setInt(const std::string &name, int value);
	void setMat4(const std::string &name, glm::mat4 value);
	void setVec3(const std::string &name, float x, float y, float z);
	void setVec3(const std::string &name, glm::vec3 value);
	void setVec4(const std::string &name, glm::vec4 value);
	void setFloat(const std::string &name, float value);
	Shader(const char* vertexPath, const char* fragPath);
	~Shader();
private:

	unsigned int compileShader(GLenum type, const char* source);
};

#endif // !DEBUG
