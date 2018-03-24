#pragma once

#include <string>
#include <glew.h>
#include "stb_image.h"
#include <cassert>
#include <iostream>

class Texture {
public:
	std::string textureAddress;
	Texture(const std::string& texAddress);
	void TextureBind(unsigned short unit);
	virtual ~Texture();
private:
	Texture(const Texture& other) {}
	Texture& operator=(const Texture& other) {}
	GLuint mTexture;

};