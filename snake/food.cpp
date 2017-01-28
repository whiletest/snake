#include "stdafx.h"
#include "food.h"
#include "head.h"

CFood::CFood(int reward /* = 0 */):m_reward(reward),m_cAppear(0)
{
	m_ptPos.x = m_ptPos.y = 0;
}

void CFood::InitialFood()
{
	m_ptPos.x = rand()%(MAX_COLS/2-5)+2;
	m_ptPos.y = rand()%(MAX_LINES-5)+2;
	m_cAppear = 0;
}

void CFood::Display(bool flag)
{
	if (!flag)
	{
		DrawString(m_ptPos.x,m_ptPos.y," ");
	}
}