#include "GL\glew.h"
#include "GL\wglew.h"
//glew has to go first.
#include "GLFW\glfw3.h"
#include "glm\glm.hpp"

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "SOIL.h"

class Sprite
{
public:
	Sprite(){};
	~Sprite(){};
	int position[4], color[4];
	unsigned int spriteID;
	int x, y, height, width;
	float uv[2];

};


class GLF
{
private:

protected:

public:
	GLF(){};
	~GLF(){};
	GLFWwindow* window;
	GLuint uiVBO;

	/*Initializes window, must specify 
	width height and title for window in that order as paramaters
	width and height as integers and title as const char**/
	int InitWindow(int a_screenWidth, int a_screenHeight, const char* a_title)
	{
		if (!glfwInit())
		{
			return -1;
		}

		window = glfwCreateWindow(a_screenWidth, a_screenHeight, a_title, NULL, NULL);
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

	GLuint uiProgramTextured = CreateProgram("VertexShader.glsl", "TexturedFragmentShader.glsl");
	GLuint MatrixIDTextured = glGetUniformLocation(uiProgramTextured, "MVP");
	float* orthographicProjection = getOrtho(0, 1024, 0, 720, 0, 100);

	//enable shaders
	glUseProgram(MatrixIDTextured);

	//ortho projection to the shader program
	glUniformMatrix4fv(MatrixIDTextured, 1, GL_FALSE, orthographicProjection);
		return 0;
	}

	GLuint CreateProgram(const char *a_vertex, const char *a_frag);
	GLuint CreateShader(GLenum a_eShaderType, const char *a_strShaderFile);
	float* getOrtho(float left, float right, float bottom, float top, float a_fNear, float a_fFar);

	/*Call shutdown after while loop before main loop returns last value 
	to properly close opengl*/
	void Shutdown()
	{
		glfwTerminate();
	}

	/*Use SetScreen to apply background color
	input paramaters in the order of rgba as floats*/
	void SetScreenColor(float a_red, float a_green, float a_blue, float a_alpha)
	{
		glClearColor(a_red, a_green, a_blue, a_alpha);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	/*used inside CreateSprite to load texture into object*/
	unsigned int loadTexture(const char* a_pFilename, int & a_iWidth, int & a_iHeight, int & a_iBPP);
	
	/*loading texture height width and bpp into shaders*/
	unsigned int CreateSprite(const char* a_textureName, int a_width, int a_height, int a_bpp);

	void UpdateDraw(Sprite& a_object);


	/*Apply Swap Buffers last in while loop, updates events and swaps buffers*/
	void SwapBuffers()
	{
		glfwSwapBuffers(window);

		//poll for and process events
		glfwPollEvents();
	}
};