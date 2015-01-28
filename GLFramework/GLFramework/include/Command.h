#ifndef _COMMAND_H_
#define _COMMAND_H_
#include "GLOBALS.h"

class Command
{
public:
	~Command(){};
	virtual void excecute() = 0;
};
#endif