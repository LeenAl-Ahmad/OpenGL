
#ifndef TEXTURE_H
#define TEXTURE_H

#include "StandardInclude.h"

class  Texture
{
public:
	virtual ~Texture();

	GLuint GetTexture() { return texture; }
	GLuint GetTexture2() { return texture2; }

	void LoadTexture(std::string _file);
	void LoadTexture2(std::string _file);
	void Cleanup();
private:

	int width = -1;
	int height = -1;
	int channels = -1;
	GLuint texture;
	GLuint texture2;
};


#endif // !TEXTURE_H
