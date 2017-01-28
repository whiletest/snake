#pragma once

#include "food.h"

class CSpecialFood:public CFood
{
public:
	CSpecialFood();
public:
	void Display(bool flag);
	bool IsTimeUp();
};