#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include "GL\glew.h"
#include "GL\wglew.h"
//glew has to go first.
#include "GLFW\glfw3.h"

#include <map>

// forward declaration
class InputHandler; 

struct CharValues
{
	unsigned int id, x0, y0 , x1, y1, width, height, xOffset, yOffset, xAdvance, scaleH;
};

class Singleton
{
public:
	static Singleton* GetInstance();
	GLFWwindow* window;
	InputHandler* input;
	std::map<int, CharValues> CharMap;

protected:
	Singleton();
	~Singleton();

	static Singleton* instance;
};
#endif