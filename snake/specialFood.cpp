#include "stdafx.h"
#include "specialFood.h"
#include "head.h"

CSpecialFood::CSpecialFood():CFood(5)
{

}

void CSpecialFood::Display(bool flag)
{
	CFood::Display(flag);

	if (flag)
	{
		DrawString(m_ptPos.x,m_ptPos.y,"бя");
	}
}

bool CSpecialFood::IsTimeUp()
{
	++m_cAppear;
	if (m_cAppear == MAX_TIME_FOOD_APPEAR)
	{
		Display(false);
		return true;
	}

	return false;
}