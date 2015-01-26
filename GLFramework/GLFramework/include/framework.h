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
	GLuint MatrixIDTextured;
	const float* ortho;
	
	enum KeyPressed{
		w = GLFW_KEY_W,
		a = GLFW_KEY_A,
		s = GLFW_KEY_S,
		d = GLFW_KEY_D,
		spacebar = GLFW_KEY_SPACE,
		esc = GLFW_KEY_ESCAPE,
		leftbutton = GLFW_MOUSE_BUTTON_LEFT,
		rightbutton = GLFW_MOUSE_BUTTON_RIGHT,
	};

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

		//alpha blend
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0);
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

	bool IsKeyPressed(KeyPressed key);

	bool IsMousePressed(KeyPressed key);
	
	glm::vec2 MousePosition();

	/*
	@ a_sprite = the sprite being animated
	@locFirstSprite is the numbers of the location of the first sprite
	to be animated {number of rows up, which column to start on}
	@totalNumOfSprites is the number of rows and columns of the sprite sheet{ column, row }
	
	first row is 0, first column is 0, starting in the bottom left corner
	 */
	


};