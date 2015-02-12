#include "framework.h"
using namespace glm;

GLF Frmwrk;

int main()
{
	Frmwrk.InitWindow(800, 600, "Hell YA!!");
	//double currentFrame, deltaTime, lastFrame = 0;
	float hAxis = 0.f;
	float vAxis = 0.f;

	Singleton * myGlobals = Singleton::GetInstance();

	myGlobals->input = new InputHandler();
	myGlobals->input->ButtonW_ = new MoveUpCommand();
	myGlobals->input->ButtonA_ = new MoveLeftCommand();
	myGlobals->input->ButtonS_ = new MoveDownCommand();
	myGlobals->input->ButtonD_ = new MoveRightCommand();

	Frmwrk.LoadCharMap("resources\\images\\Arial.fnt");
	Sprite font("resources\\images\\Arial_0.png");

	float location[2]{80, 80};
	float location2[2]{400,300};
	int size[2]{150, 150};
	int size2[2]{150, 150};
	
	//loading values into vec4 for uv coordinates
	std::vector<vec2> AsUV_s;

	float x_s = 0.f, y_s = 0.f, z_s = 1.f, w_s = 1.f;
	AsUV_s.push_back(glm::vec2(x_s, y_s));
	AsUV_s.emplace_back(glm::vec2(x_s, w_s));
	AsUV_s.emplace_back(glm::vec2(z_s, w_s));
	AsUV_s.emplace_back(glm::vec2(z_s, y_s));

	Sprite AnimatedObject("resources\\images\\TestGokuAlpha.png", location, size);
	Sprite TestObject("resources\\images\\Astroid.png", location2, size2, AsUV_s);


	while (!glfwWindowShouldClose(Singleton::GetInstance()->window))
	{
		Frmwrk.SetScreenColor(0.2f, 0.2f, 0.25f, 0.0f);
		Frmwrk.currentFrame = glfwGetTime();
		Frmwrk.deltaTime = Frmwrk.currentFrame - Frmwrk.lastFrame;
		Frmwrk.lastFrame = Frmwrk.currentFrame;

		myGlobals->input->HandleInput();

		Frmwrk.DrawString(font,"Goku kickin butt", 10, 400);

		hAxis = myGlobals->input->horzAxis;
		vAxis = myGlobals->input->vertAxis;

		location2[0] += 100 * (hAxis * Frmwrk.deltaTime);
		location2[1] += 100 * (vAxis * Frmwrk.deltaTime);

		//Animate test calls
		Frmwrk.AnimateSprite(AnimatedObject, 5);
		//input handling test calls
		Frmwrk.DrawSprite(AnimatedObject);
		
		TestObject.UpdateVertices(location2, size2);
		Frmwrk.DrawSprite(TestObject);

		Frmwrk.SwapBuffers();
	}
	
	delete myGlobals->input->ButtonW_;
	delete myGlobals->input->ButtonA_;
	delete myGlobals->input->ButtonS_;
	delete myGlobals->input->ButtonD_;
	delete myGlobals->input;

	Frmwrk.Shutdown();
}
