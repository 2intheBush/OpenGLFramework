#include <GLOBALS.h>

//Static member
Singleton* Singleton::instance = 0;

Singleton::Singleton()
{
}
Singleton::~Singleton()
{
}

//Function for providing access to the class
Singleton* Singleton::GetInstance()
{
	//If no instance exists, create one
	if (instance == 0)
	{
		//Create instance
		instance = new Singleton();
	}
	return instance;
}

