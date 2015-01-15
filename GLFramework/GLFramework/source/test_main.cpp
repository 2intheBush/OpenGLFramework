#include "framework.h"
#include "TestObj.h"

void InitTestObject();

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

void InitTestObject()
{
	TestObject Player;
	Player.x = Player.y = 300;
	Player.width = Player.height = 50;

}