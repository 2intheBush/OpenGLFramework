#include "framework.h"
#include "TestObj.h"

GLF Frmwrk;

int main()
{
	Frmwrk.InitWindow(600, 600, "Hell YA!!");
	while (!glfwWindowShouldClose(Frmwrk.window))
	{
		Frmwrk.SetScreenColor(0.5f, 1.0f, 0.25f, .0f);
		

		Frmwrk.SwapBuffers();
	}
	Frmwrk.Shutdown();
}
