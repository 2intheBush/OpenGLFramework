#include "framework.h"
#include "TestObj.h"

using namespace glm;

GLF Frmwrk;


int main()
{
	Frmwrk.InitWindow(800, 600, "Hell YA!!");
	double currentFrame, deltaTime, lastFrame = 0;

	float location[2]{720, 80};
	float location2[2]{400,300};
	int size[2]{150, 150};
	int size2[2]{150, 150};
	
	//loading values into vec4 for uv coordinates
	float x = 0.015f, y = .882f, z = .1f, w = .99f;
	std::vector<vec2> UVList;
	std::vector<vec2> AsUV_s;
	UVList.push_back(glm::vec2(x, y));
	UVList.emplace_back(glm::vec2(x, w));
	UVList.emplace_back(glm::vec2(z, w));
	UVList.emplace_back(glm::vec2(z, y));

	float x_s = 0.f, y_s = 0.f, z_s = 1.f, w_s = 1.f;
	AsUV_s.push_back(glm::vec2(x_s, y_s));
	AsUV_s.emplace_back(glm::vec2(x_s, w_s));
	AsUV_s.emplace_back(glm::vec2(z_s, w_s));
	AsUV_s.emplace_back(glm::vec2(z_s, y_s));

	//std::cout<<"0 = " << UVList[0].x << ", " << UVList[0].y << std::endl;
	//std::cout << "1 = " << UVList[1].x << ", " << UVList[1].y << std::endl;
	//std::cout << "2 = " << UVList[2].x << ", " << UVList[2].y << std::endl;
	//std::cout << "3 = " << UVList[3].x << ", " << UVList[3].y << std::endl;

	Sprite AnimatedObject("resources\\images\\TestGokuC.png", location, size, UVList);
	Sprite TestObject("resources\\images\\Astroid.png", location2, size2, AsUV_s);
	double animTimer = .075;		
	double timeCount = 0;
	double animationCount = 0;
	
	while (!glfwWindowShouldClose(Frmwrk.window))
	{
		Frmwrk.SetScreenColor(0.2f, 0.2f, 0.25f, 0.0f);
		currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		if (Frmwrk.IsKeyPressed(Frmwrk.w))
		{
			location2[1] += 200.f * deltaTime;
		};
		if (Frmwrk.IsKeyPressed(Frmwrk.a))
		{
			location2[0] -= 200.f * deltaTime;
		};
		if (Frmwrk.IsKeyPressed(Frmwrk.s))
		{
			location2[1] -= 200.f* deltaTime;
		};
		if (Frmwrk.IsKeyPressed(Frmwrk.d))
		{
			location2[0] += 200.f* deltaTime;
		};
		if (Frmwrk.IsMousePressed(Frmwrk.leftbutton))
		{
			size2[0] = size2[1] += 1.f;
			glm::vec2 mouPos = Frmwrk.MousePosition();
			std::cout << mouPos.x << ", " << mouPos.y << std::endl;
		}
		if (Frmwrk.IsMousePressed(Frmwrk.rightbutton))
		{
			size2[0] = size2[1] -= 1.f * deltaTime;
			glm::vec2 mouPos = Frmwrk.MousePosition();
			std::cout << mouPos.x << ", " << mouPos.y << std::endl;
		}
		
		//Animate test calls
		timeCount = timeCount + deltaTime;
		if (animTimer < timeCount)
		{
			Frmwrk.AnimateSprite(AnimatedObject);
			timeCount = 0;
			animationCount++;
		}
		if (animationCount > 5)
		{
			UVList.pop_back();
			UVList.pop_back();
			UVList.pop_back();
			UVList.pop_back();
			x = 0.015f, y = .882f, z = .1f, w = .99f;
			UVList.push_back(glm::vec2(x, y));
			UVList.emplace_back(glm::vec2(x, w));
			UVList.emplace_back(glm::vec2(z, w));
			UVList.emplace_back(glm::vec2(z, y));
			animationCount = 0;
		
			for (int i = 0; i < 4; i++)
			{
				AnimatedObject.vertices[i].uv[0] = UVList[i].x;
				AnimatedObject.vertices[i].uv[1] = UVList[i].y;
			}
		}
		//input handling test calls
		Frmwrk.DrawSprite(AnimatedObject);
		
		TestObject.UpdateVertices(location2, size2);
		Frmwrk.DrawSprite(TestObject);

		Frmwrk.SwapBuffers();
	}
	Frmwrk.Shutdown();
}