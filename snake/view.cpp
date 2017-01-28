#include "stdafx.h"
#include "view.h"
#include <ctime>
#include "normalFood.h"
#include "specialFood.h"


CMyView::CMyView(HWND hwnd /* = 0 */):m_hwnd(hwnd),
                                      m_score(0),
									  m_cToCreateSF(0)
{
	for (int i = 0;i != MAX_NUM_FOOD_APPEAR;++i)
		m_pFood[i] = 0;
}

CMyView::~CMyView()
{
	for (int i = 0;i != MAX_NUM_FOOD_APPEAR;++i)
		if (m_pFood[i])
			delete m_pFood[i];
}

void CMyView::InitialGui()
{
	//设置控制台行列个数
	system("mode con cols=81 lines=30");

	int i=5;
	DrawString(10,i++," _____   __   _       ___   _   _    _____  ");
	DrawString(10,i++,"/  ___/ |  \\ | |     /   | | | / /  | ____| ");
	DrawString(10,i++,"| |___  |   \\| |    / /| | | |/ /   | |__   ");
	DrawString(10,i++,"\\___  \\ | |\\   |   / / | | | |\\ \\   |  __|  ");
	DrawString(10,i++," ___| | | | \\  |  / /  | | | | \\ \\  | |___  ");
	DrawString(10,i++,"/_____/ |_|  \\_| /_/   |_| |_|  \\_\\ |_____| ");
	DrawString(10,++i,"贪吃蛇 - By while build:2012.09");
	i=14;
	DrawString(10,i++,"◎：蛇的身体，不能吃到自己，不能去啃墙- -!");
	DrawString(10,i++,"◆：普通食物，吃掉一个加一分");
	DrawString(10,i++,"★：高分食物，吃掉一个加五分（每吃5个普通食物才会产生）");
	i=21;
	DrawString(13,i++,"-- 按下任意键开始游戏 --");
	DrawString(19,i++,"");
	_getch();
}

void CMyView::ShowScore()
{
	DrawString(3,0,"score:%d%d%d",m_score/100,m_score%100/10,m_score%10);
}

void CMyView::InitialFood()
{
	for (int i = 0;i != MAX_NUM_FOOD_APPEAR;++i)
		if (m_pFood[i])
			delete m_pFood[i];

	m_pFood[0] = new CNormalFood;
	m_pFood[0]->InitialFood();
	m_pFood[0]->Display(true);

	m_pFood[1] = 0;
}


void CMyView::SnakeEatFood()
{
	for (int i = 0;i != MAX_NUM_FOOD_APPEAR;++i)
	{
		if (m_pFood[i])
		{
			if (m_pFood[i]->IsTimeUp())
			{
				if (i == 1)
				{
					delete m_pFood[i];
					m_pFood[i] = 0;
					break;
				}
			}

			int temScore = m_snake.IsEatFood(m_pFood[i]);
			if (temScore)
			{
				m_score += temScore;

				if (i != 1)
				{
					CreateFood(0);

					m_cToCreateSF += temScore;
					if (m_cToCreateSF == MAX_COUNT_TO_CREATE_SPECIAL_FOOD)
					{
						m_cToCreateSF = 0;
						CreateFood(1);
					}
				}
			}
		}
	}
}

void CMyView::CreateFood(int type)
{
	if (type == 0)
	{
		m_pFood[type]->InitialFood();
	}
	else if (type == 1)
	{
		CFood *pFood = new CSpecialFood;
		pFood->InitialFood();
		m_pFood[type] = pFood;
	}

	m_pFood[type]->Display(true);
}

void CMyView::Start()
{
	system("CLS");
	m_wall.InitialWall();
	m_snake.InitialSnake();
	InitialFood();
	m_score = 0;
}

void CMyView::Display()
{
	m_snake.Move();
	ShowScore();

	if (   m_wall.HitWall(m_snake.getHeadPosition())
		|| m_snake.IsEatSelf() )
	{
		DrawString(1,1,"你挂了,任意键重玩.");

		_getch();
		Start();

		return;
	}

	SnakeEatFood();
}

bool CMyView::HandleMessage()
{
	//按下非字符的特殊键返回224
	if (_getch() == 224)
	{
		int ch = _getch();
		switch (ch)
		{
		case 72: //上
			return m_snake.ChangeDirection(direct_up);
		case 77: //右
			return m_snake.ChangeDirection(direct_right);
		case 80: //下
			return m_snake.ChangeDirection(direct_down);
		case 75: //左
			return m_snake.ChangeDirection(direct_left);
		}
	}
	
	return false;
}