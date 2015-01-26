#include "framework.h"
#include "TestObj.h"

using namespace glm;

GLF Frmwrk;


int main()
{
	Frmwrk.InitWindow(800, 600, "Hell YA!!");

	float location[2]{300, 300};
	int size[2]{150, 150};

	//loading values into vec4 for uv coordinates
	float x = 0.0f, y = 0.0f, z = 1.f, w = 1.f;
	std::vector<vec2> UVList;
	UVList.push_back(glm::vec2(x, y));
	UVList.emplace_back(glm::vec2(z, y));
	UVList.emplace_back(glm::vec2(z, w));
	UVList.emplace_back(glm::vec2(x, w));

	//std::cout<<"0 = " << UVList[0].x << ", " << UVList[0].y << std::endl;
	//std::cout << "1 = " << UVList[1].x << ", " << UVList[1].y << std::endl;
	//std::cout << "2 = " << UVList[2].x << ", " << UVList[2].y << std::endl;
	//std::cout << "3 = " << UVList[3].x << ", " << UVList[3].y << std::endl;

	Sprite AnimatedObject("resources\\images\\Astroid.png", location, size, UVList);
	
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
		
		//Animate test calls
		//Frmwrk.Animate(AnimatedObject, locFirst, totalNum, 2);

		//input handling test calls
		AnimatedObject.UpdateVertices(location, size);

		Frmwrk.DrawSprite(AnimatedObject);

		Frmwrk.SwapBuffers();
	}
	Frmwrk.Shutdown();
}

