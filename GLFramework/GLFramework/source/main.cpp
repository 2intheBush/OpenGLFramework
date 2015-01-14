#include "framework.h"

int main()
{
	GLF::InitWindow(600, 600, "Hell YA!!");
	
	while (!glfwWindowShouldClose(GLF::window))
	{
		GLF::SetScreen(0.5f, 1.0f, 0.25f, .0f);


		GLF::SwapBuffers();
	}
	GLF::Shutdown();
}