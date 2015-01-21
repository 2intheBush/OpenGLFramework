#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "GL\glew.h"
#include "GL\wglew.h"
//glew has to go first.
#include "GLFW\glfw3.h"
#include "glm\glm.hpp"
#include <vector>
#include <string>
#include "SOIL.h"
#include <fstream>
#include <iostream>

struct Vertex
{
	float position[4];
	float color[4];
	float uv[2];
};

class Sprite
{
public:
	/*o_loc is location of the object the sprite is representing [x,y]
	o_size is the size of the object the sprite is representing [width, height]
	width and hieght must be ints */
	Sprite(const char* o_fileName, float o_loc[2], int o_size[2]);
	
	~Sprite(){};
	Vertex vertices[4];
	
	int bpp;
	unsigned int spriteID;
	GLuint uiVBO;
	GLuint uiIBO;
	unsigned int loadTexture(const char* a_pFilename, int & a_iWidth, int & a_iHeight, int & a_iBPP);
};
#endif

