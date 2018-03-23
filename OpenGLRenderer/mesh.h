#pragma once

#include <glm.hpp>
#include <glew.h>

class Vertex{
public:
	Vertex(const glm::vec3& pos){
		this->pos = pos;
	}
private:
	glm::vec3 pos;
};

class Mesh {
public:
	Mesh(Vertex* vertices, unsigned int numVertices);
	void Draw();
	virtual ~Mesh();
private:

	enum {
		POSITION_VB,
		NUM_BUFFERS
	};

	Mesh(const Mesh& other) {}
	Mesh& operator=(const Mesh& other) {}
	GLuint VertexArrayObject;
	GLuint VertexArrayBuffers[NUM_BUFFERS];
	unsigned int DrawCount;
};