#include "framework.h"
#include "Vegeta.h" 

//Vegeta vegeta;
GLF Frame;


int main()
{
	Frame.InitWindow(1024, 720, "Goku Kicks butt");


	while (!glfwWindowShouldClose(Singleton::GetInstance()->window))
	{
		Frame.SetScreenColor(0.2f, 0.2f, 0.25f, 0.0f);
		//vegeta.Initialize();
	

		Frame.SwapBuffers();
	}
	Frame.Shutdown();
}