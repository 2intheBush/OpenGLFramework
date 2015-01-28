#include <SubCommand.h>

bool InputHandler::IsKeyPressed(KeyPressed key)
{
	return glfwGetKey(Singleton::GetInstance()->window, key);
}

void MoveUpCommand::MoveUp()
{
	Singleton::GetInstance()->input->vertAxis = 1.f;
}

void MoveDownCommand::MoveDown()
{
	Singleton::GetInstance()->input->vertAxis = -1.f;
}

void MoveLeftCommand::MoveLeft()
{
	Singleton::GetInstance()->input->horzAxis = -1.f;
}

void MoveRightCommand::MoveRight()
{
	Singleton::GetInstance()->input->horzAxis = 1.f;
}
