#include "mesh.h"

Mesh::Mesh(Vertex* vertices, unsigned int numVertices) {
	DrawCount = numVertices;
	glGenVertexArrays(1, &VertexArrayObject);
	glBindVertexArray(VertexArrayObject);

	glGenBuffers(1, VertexArrayBuffers);
	glBindBuffer(GL_ARRAY_BUFFER, VertexArrayBuffers[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(vertices[0]), vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (const void*)0);

	glBindVertexArray(0);
}

Mesh::~Mesh(){
	glDeleteVertexArrays(1, &VertexArrayObject);
}

void Mesh::Draw() {
	glBindVertexArray(VertexArrayObject);

	glDrawArrays(GL_TRIANGLES, 0, DrawCount);

	glBindVertexArray(0);
}