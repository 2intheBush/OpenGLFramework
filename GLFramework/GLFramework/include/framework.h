#include "GL\glew.h"
#include "GL\wglew.h"
//glew has to go first.
#include "GLFW\glfw3.h"
#include "glm\glm.hpp"

class GLF
{
private:
protected:
public:
	/*Initializes window, must specify 
	width height and title for window in that order as paramaters
	width and height as integers and title as const char**/
	static int InitWindow(int a_screenWidth, int a_screenHeight, const char* a_title)
	{
		if (!glfwInit())
		{
			return -1;
		}
		GLFWwindow* window = glfwCreateWindow(a_screenWidth, a_screenHeight, a_title, NULL, NULL);
		if (!window)
		{
			glfwTerminate();
			return -1;
		}
		//make the window's context current
		glfwMakeContextCurrent(window);

		//Start GLEW
		if (glewInit() != GLEW_OK)
		{
			//OpenGL didn't Start up... Shutdown GLFW and return an error code
			glfwTerminate();
			return -1;
		}
		return 0;
	}
	static void Shutdown()
	{
		glfwTerminate();
	}
};