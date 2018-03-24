#pragma once

#include <string>
#include <glew.h>
#include <iostream>
#include "transform.h"
#include "camera.h"
#define SHADER_NUMBER 2

class Shader {
public:
	std::string shaderAddress;
	Shader(const std::string& fileName);
	virtual ~Shader();
	void ShaderBind();
	void ShaderUpdate(const Transform& transform, const Camera& camera);
private:

	enum {
		TRANSFORM_UNIFORM,
		NUM_UNIFORMS
	};

	Shader(const Shader& other) {}
	Shader& operator=(const Shader& other) {}
	GLuint program;
	GLuint shaders[SHADER_NUMBER];
	GLuint uniforms[NUM_UNIFORMS];
};