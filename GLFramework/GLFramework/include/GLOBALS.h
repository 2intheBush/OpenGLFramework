#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include "GL\glew.h"
#include "GL\wglew.h"
//glew has to go first.
#include "GLFW\glfw3.h"

// forward declaration
class InputHandler;

class Singleton
{
public:
	static Singleton* GetInstance();
	GLFWwindow* window;
	InputHandler* input;

protected:
	Singleton();
	~Singleton();
	
	static Singleton* instance;

};




#endif

