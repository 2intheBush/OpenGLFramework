#include "Sprite.h"

class GLF
{
private:

protected:

public:
	GLF(){};
	~GLF(){};
	GLFWwindow* window;
	GLuint uiProgramTextured;
	GLuint MatrixIDTextured = -1;
	const float* ortho;

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
		ortho = getOrtho(0, a_screenWidth, 0, a_screenHeight, 0, 100);
		uiProgramTextured = CreateProgram("VertexShader.glsl", "TexturedFragmentShader.glsl");
		MatrixIDTextured = glGetUniformLocation(uiProgramTextured, "MVP");
		return 0;
	}

	void DrawSprite(Sprite& s_object);

	GLuint CreateProgram(const char *a_vertex, const char *a_frag);
	GLuint CreateShader(GLenum a_eShaderType, const char *a_strShaderFile);
	const float* getOrtho(float left, float right, float bottom, float top, float a_fNear, float a_fFar);

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

	/*Apply Swap Buffers last in while loop, updates events and swaps buffers*/
	void SwapBuffers()
	{
		glfwSwapBuffers(window);

		//poll for and process events
		glfwPollEvents();
	}
};