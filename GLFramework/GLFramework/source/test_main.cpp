#include "framework.h"
#include "TestObj.h"

GLF Frmwrk;

int main()
{
	Frmwrk.InitWindow(800, 600, "Hell YA!!");

	float location[2]{300, 300};
	int size[2]{50,50};

	Sprite testobject("resources\\images\\Astroid.png", location, size);

	while (!glfwWindowShouldClose(Frmwrk.window))
	{
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0);
		Frmwrk.SetScreenColor(0.2f, 0.2f, 0.25f, 0.0f);
		Frmwrk.DrawSprite(testobject);

		Frmwrk.SwapBuffers();
	}
	Frmwrk.Shutdown();
}
