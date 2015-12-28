//
//  Texture.cpp
//  CrappyBird
//
//  Created by Dean Becker on 20/12/2015.
//  Copyright � 2015 Dean Becker. All rights reserved.

#include "Texture.hpp"

extern "C" {
	#include "TextureUtils.h"
}

static int activeTextures = 0;

Texture::Texture(std::string filePath)
{
	/// Home grown texture loading
	TextureData data = getTextureData(filePath.c_str());
	///
	width = data.width;
	height = data.height;
	textureId = data.Id;
}

Texture::~Texture()
{
}

void Texture::bind()
{
	glBindTexture(GL_TEXTURE_2D, textureId);
}

void Texture::unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}