#pragma once

#include <string>
#include <glew.h>
#include <iostream>
#define SHADER_NUMBER 2

class Shader {
public:
	Shader(const std::string& fileName);
	virtual ~Shader();
	void Bind();
private:
	Shader(const Shader& other) {}
	Shader& operator=(const Shader& other) {}
	GLuint program;
	GLuint shaders[SHADER_NUMBER];
};