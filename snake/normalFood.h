#pragma once

#include "food.h"

class CNormalFood:public CFood
{
public:
	CNormalFood();
public:
	void Display(bool flag);
	bool IsTimeUp();
};