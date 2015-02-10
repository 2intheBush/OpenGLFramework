#ifndef _VEGETA_H_
#define _VEGETA_H_





enum AnimationType
{
	idle,
	walk
};

class Vegeta
{
public:
	float x, y, width, height;

	void Initialize();
};

#endif
