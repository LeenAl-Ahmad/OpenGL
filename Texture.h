#ifndef TEXTURE_H
#define TEXTURE_H

#include "StandardInclude.h"

class  Texture
{
public:
	virtual ~Texture();

	GLuint GetTexture() { return texture; }

	void LoadTexture(std::string _file);
	void Cleanup();
private:

	int width = -1;
	int height = -1;
	int channels = -1;
	GLuint texture;
};


#endif // !TEXTURE_H

