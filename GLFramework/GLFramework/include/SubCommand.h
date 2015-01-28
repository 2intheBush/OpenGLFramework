#ifndef _SUBCOMMAND_H_
#define _SUBCOMMAND_H_

#include "Command.h"

enum KeyPressed{
	w = GLFW_KEY_W,
	a = GLFW_KEY_A,
	s = GLFW_KEY_S,
	d = GLFW_KEY_D,
	spacebar = GLFW_KEY_SPACE,
	esc = GLFW_KEY_ESCAPE,
	leftbutton = GLFW_MOUSE_BUTTON_LEFT,
	rightbutton = GLFW_MOUSE_BUTTON_RIGHT,
};




class MoveUpCommand : public Command
{
	public:
		virtual void excecute(){ MoveUp(); };
private:
	void MoveUp();
};

class MoveDownCommand : public Command
{
public:
	virtual void excecute(){ MoveDown(); };
private:
	void MoveDown();
};

class MoveLeftCommand : public Command
{
public:
	virtual void excecute(){ MoveLeft(); };
private:
	void MoveLeft();
};

class MoveRightCommand : public Command
{
public:
	virtual void excecute(){ MoveRight(); };
private:
	void MoveRight();
};

class InputHandler
{
public:
	void HandleInput()
	{
		vertAxis = horzAxis = 0;
		if (IsKeyPressed(w)) ButtonW_->excecute();
		if (IsKeyPressed(a)) ButtonA_->excecute();
		if (IsKeyPressed(s)) ButtonS_->excecute();
		if (IsKeyPressed(d)) ButtonD_->excecute();
	}

	Command* ButtonW_;
	Command* ButtonA_;
	Command* ButtonS_;
	Command* ButtonD_;

	float vertAxis;
	float horzAxis;
private:


	bool IsKeyPressed(KeyPressed key);
};

#endif