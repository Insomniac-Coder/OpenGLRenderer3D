#pragma once

#include <string>
#include <glew.h>
#include "stb_image.h"

class Texture {
public:
	Texture(const std::string& fileName);
	void Bind(unsigned short unit);
	virtual ~Texture();
private:
	Texture(const Texture& other) {}
	Texture& operator=(const Texture& other) {}
	GLuint mTexture;

};