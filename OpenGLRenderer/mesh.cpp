#include "mesh.h"

Mesh::Mesh(const std::string& fileName, const std::string& TextureAddress, const std::string& ShaderAddress) : Texture(TextureAddress), Shader(ShaderAddress){
	IndexedModels model = OBJModel(fileName).ToIndexedModel();
	InitMesh(model);
	textureAddress = TextureAddress;
	shaderAddress = ShaderAddress;
}

Mesh::Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices, const std::string& TextureAddress, const std::string& ShaderAddress) : Texture(TextureAddress), Shader(ShaderAddress) {
	//DrawCount = numVertices;
	//DrawCount = numIndicies;

	//std::vector<glm::vec3> positions;
	//std::vector<glm::vec2> texCoords;

	//positions.reserve(numVertices);
	//texCoords.reserve(numVertices);
	IndexedModels model;

	for (unsigned int i = 0; i < numVertices; i++) {
		model.positions.push_back(*vertices[i].GetPos());
		model.texCoords.push_back(*vertices[i].GetTexCoord());
		model.normals.push_back(*vertices[i].GetNormal());
	}

	for (unsigned int i = 0; i < numIndices; i++)
		model.indices.push_back(indices[i]);
	InitMesh(model);
	textureAddress = TextureAddress;
	shaderAddress = ShaderAddress;
}

void Mesh::InitMesh(const IndexedModels& model) {
	DrawCount = model.indices.size();
	glGenVertexArrays(1, &VertexArrayObject);
	glBindVertexArray(VertexArrayObject);

	glGenBuffers(NUM_BUFFERS, VertexArrayBuffers);

	glBindBuffer(GL_ARRAY_BUFFER, VertexArrayBuffers[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.positions[0]), &model.positions[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (const void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, VertexArrayBuffers[TEXCOORD_VB]);
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.texCoords[0]), &model.texCoords[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (const void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, VertexArrayBuffers[NORMAL_VB]);
	glBufferData(GL_ARRAY_BUFFER, model.normals.size() * sizeof(model.normals[0]), &model.normals[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (const void*)0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VertexArrayBuffers[INDEX_VB]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(model.indices[0]), &model.indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);
}

Mesh::~Mesh(){
	glDeleteVertexArrays(1, &VertexArrayObject);
}

void Mesh::Draw(const Camera& cam) {
	glBindVertexArray(VertexArrayObject);

	glDrawElements(GL_TRIANGLES, DrawCount, GL_UNSIGNED_INT, (const void *)0);
	//glDrawArrays(GL_TRIANGLES, 0, DrawCount);

	glBindVertexArray(0);

	TextureBind(0);
	ShaderBind();
	ShaderUpdate(Transform(*this), cam);
}