#pragma once

#include <glm.hpp>
#include <glew.h>
#include <vector>
#include "objloader.h"
#include <iostream>
#include "texture.h"
#include "camera.h"
#include "shader.h"
#include "transform.h"

class Vertex{
public:
	Vertex(const glm::vec3& pos, const glm::vec2& texCoord, const glm::vec3& normal = glm::vec3(0.0f, 0.0f, 0.0f)){
		this->pos = pos;
		this->texCoord = texCoord;
		this->normal = normal;
	}

	inline glm::vec3* GetPos() { return &pos; }
	inline glm::vec2* GetTexCoord() { return &texCoord; }
	inline glm::vec3* GetNormal() { return &normal; }
private:
	glm::vec3 pos;
	glm::vec2 texCoord;
	glm::vec3 normal;
};

class Mesh : public Texture, public Shader, public Transform{
public:

	Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndicies, const std::string& TextureAddress, const std::string& ShaderAddress);
	Mesh(const std::string& fileName, const std::string& TextureAddress, const std::string& ShaderAddress);
	void Draw(const Camera& cam);
	virtual ~Mesh();

private:
	void InitMesh(const IndexedModels& model);

	enum {
		POSITION_VB,
		TEXCOORD_VB,
		NORMAL_VB,
		INDEX_VB,
		NUM_BUFFERS
	};

    Mesh(const Mesh& other) : Texture(other.textureAddress), Shader(other.shaderAddress) {}
	Mesh& operator=(const Mesh& other) {}
	GLuint VertexArrayObject;
	GLuint VertexArrayBuffers[NUM_BUFFERS];
	unsigned int DrawCount;
};