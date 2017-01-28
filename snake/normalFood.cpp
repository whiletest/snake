#include "stdafx.h"
#include "normalFood.h"
#include "head.h"

CNormalFood::CNormalFood():CFood(1)
{

}

void CNormalFood::Display(bool flag)
{
	CFood::Display(flag);

	if (flag)
	{
		DrawString(m_ptPos.x,m_ptPos.y,"¡ô");
	}
}

bool CNormalFood::IsTimeUp()
{
	++m_cAppear;
	if (m_cAppear == MAX_TIME_FOOD_APPEAR)
	{
		Display(false);
		InitialFood();
		Display(true);

		return true;
	}

	return false;
}