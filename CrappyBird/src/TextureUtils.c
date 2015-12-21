#include "TextureUtils.h"

GLuint getTextureData(const char * filePath)
{
	// Broken .bmp file parsing????
	FILE* f = fopen(filePath, "rb");
	if (!f) printf("Could not open: %s\n", filePath);

	char header[54];
	int dataPos, imageSize, width, height;

	if (fread(header, 1, 54, f) != 54) 
		if (header[0] != 'B' || header[1] != 'M') printf("Invalid .bmp format: %s\n", filePath);
	
	// Header data
	dataPos = *(int *)&(header[0x0A]);
	imageSize = *(int*)&(header[0x22]);
	width = *(int *)&(header[0x12]);
	height = *(int *)&(header[0x16]);

	if (imageSize == 0) imageSize = (width *height * 3);
	if (dataPos == 0) dataPos = 54;

	size_t dMul = sizeof(unsigned char);
	unsigned char* data = (unsigned char*)malloc(imageSize * dMul);
	fread(data, 1, imageSize, f);

	fclose(f);
	if (f) free(f);

	// Probably working opengl texture binding
	GLuint textureId;
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);

#ifdef _WIN32
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
#endif
#ifdef __APPLE__
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
#endif

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	glBindTexture(GL_TEXTURE_2D, 0);
	if (data) free(data);

	return textureId;
}
