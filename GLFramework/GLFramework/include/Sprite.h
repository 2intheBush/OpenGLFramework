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
#include "GLOBALS.h"

struct Vertex
{
	float position[4];
	float color[4];
	/*
	GPU only knows base types (ie floats, ints) not created types (std::vector)
	you can use it, but you'll have to extract it to floats before sending, that is what 
	this struct is for.  
	bottom line, keep this floats
	*/
	//std::vector<glm::vec2> uv;
	float uv[2];
};

class Sprite
{
public:
	/*
	o_loc is location of the object the sprite is representing {x,y}
	o_size is the size of the object the sprite is representing {width, height}
	width and hieght must be ints
	this constructor for sprites to be animated
	set uvCoordinates to a  vector 4 as {x1, y1, x2, y2}
	*/
	Sprite(const char* o_fileName, float o_loc[2], int o_size[2], std::vector<glm::vec2> UVList);
	Sprite(const char* oFileName, int location[2], char ch);
	~Sprite(){};
	Vertex vertices[4];
	int bpp;
	unsigned int spriteID;
	GLuint uiVBO;
	GLuint uiIBO;
	unsigned int loadTexture(const char* a_pFilename, int & a_iWidth, int & a_iHeight, int & a_iBPP);

	void UpdateVertices(float o_loc[2], int o_size[2]);
};
#endif

