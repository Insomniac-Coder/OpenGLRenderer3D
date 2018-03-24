#include"texture.h"

Texture::Texture(const std::string& texAddress) : textureAddress(texAddress) {
	int width, height, NumComponents;

	unsigned char* imageData = stbi_load(textureAddress.c_str(), &width, &height, &NumComponents, 4);

	if (imageData == NULL)
		std::cerr << "Texture loading failed for texture : " + textureAddress << std::endl;

	glGenTextures(1, &mTexture);
	glBindTexture(GL_TEXTURE_2D, mTexture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

	stbi_image_free(imageData);
}

void Texture::TextureBind(unsigned short unit) {
	assert(unit >= 0 && unit <= 31);

	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, mTexture);
}

Texture::~Texture() {
	glDeleteTextures(1, &mTexture);
}