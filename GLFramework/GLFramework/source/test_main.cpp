#include "framework.h"
#include "TestObj.h"

GLF Frmwrk;

Sprite* object = new Sprite[4];

void InitTestObj();


int main()
{
	Frmwrk.InitWindow(600, 600, "Hell YA!!");

	void InitTestObj();
	while (!glfwWindowShouldClose(Frmwrk.window))
	{
		Frmwrk.SetScreenColor(0.5f, 1.0f, 0.25f, .0f);
		
		Frmwrk.CreateSprite("resources\\images\\Astroid.png",object[0].width, object[0].height, 4);
		Frmwrk.UpdateDraw(*object);

		Frmwrk.SwapBuffers();
	}
	Frmwrk.Shutdown();
}


void InitTestObj()
{
	for (int i = 0; i < 4; i++)
	{
		object[i].position[2] = 0;
		object[i].position[3] = 1;
		object[i].color[0] = 1;
		object[i].color[1] = 1;
		object[i].color[2] = 1;
		object[i].color[3] = 1;
		object[i].x = object[i].y = 300;
		object[i].height = object[i].width = 50;
	}
	

	object[0].position[0] = object[0].x - object[0].height * .5;
	object[0].position[1] = object[0].y - object[0].height * .5;
	object[1].position[0] = object[1].x - object[1].height * .5;
	object[1].position[1] = object[1].y + object[1].height * .5;
	object[2].position[0] = object[2].x + object[2].height * .5;
	object[2].position[1] = object[2].y + object[2].height * .5;
	object[3].position[0] = object[3].x + object[3].height * .5;
	object[3].position[1] = object[3].y - object[3].height * .5;
	
	object[0].uv[0] = 0;
	object[0].uv[1] = 1;
	object[1].uv[0] = 0;
	object[1].uv[1] = 0;
	object[2].uv[0] = 1;
	object[2].uv[1] = 0;
	object[3].uv[0]	= 1;
	object[3].uv[1] = 1;
}