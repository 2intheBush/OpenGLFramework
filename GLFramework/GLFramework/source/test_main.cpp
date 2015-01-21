#include "framework.h"
#include "TestObj.h"

GLF Frmwrk;

int main()
{
	Frmwrk.InitWindow(800, 600, "Hell YA!!");

	float location[2]{300, 300};
	int size[2]{50, 50};

	Sprite testobject("resources\\images\\Astroid.png", location, size);
	
	Frmwrk.AddFont("resources\\images\\font.png");

	while (!glfwWindowShouldClose(Frmwrk.window))
	{
		Frmwrk.SetScreenColor(0.2f, 0.2f, 0.25f, 0.0f);

		if (Frmwrk.IsKeyPressed(Frmwrk.w))
		{
			location[1] += .2f;
		};
		if (Frmwrk.IsKeyPressed(Frmwrk.a))
		{
			location[0] -= .2f;
		};
		if (Frmwrk.IsKeyPressed(Frmwrk.s))
		{
			location[1] -= .2f;
		};
		if (Frmwrk.IsKeyPressed(Frmwrk.d))
		{
			location[0] += .2f;
		};
		if (Frmwrk.IsMousePressed(Frmwrk.leftbutton))
		{
			size[0] = size[1] += 1.f;
			glm::vec2 mouPos = Frmwrk.MousePosition();
			std::cout << mouPos.x << ", " << mouPos.y << std::endl;
		}
		if (Frmwrk.IsMousePressed(Frmwrk.rightbutton))
		{
			size[0] = size[1] -= 1.f;
			glm::vec2 mouPos = Frmwrk.MousePosition();
			std::cout << mouPos.x << ", " << mouPos.y << std::endl;
		}

		testobject.UpdateVertices(location, size);
		Frmwrk.DrawSprite(testobject);
		Frmwrk.SwapBuffers();
	}
	Frmwrk.Shutdown();
}

