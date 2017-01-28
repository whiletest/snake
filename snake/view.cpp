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
	//���ÿ���̨���и���
	system("mode con cols=81 lines=30");

	int i=5;
	DrawString(10,i++," _____   __   _       ___   _   _    _____  ");
	DrawString(10,i++,"/  ___/ |  \\ | |     /   | | | / /  | ____| ");
	DrawString(10,i++,"| |___  |   \\| |    / /| | | |/ /   | |__   ");
	DrawString(10,i++,"\\___  \\ | |\\   |   / / | | | |\\ \\   |  __|  ");
	DrawString(10,i++," ___| | | | \\  |  / /  | | | | \\ \\  | |___  ");
	DrawString(10,i++,"/_____/ |_|  \\_| /_/   |_| |_|  \\_\\ |_____| ");
	DrawString(10,++i,"̰���� - By while build:2012.09");
	i=14;
	DrawString(10,i++,"���ߵ����壬���ܳԵ��Լ�������ȥ��ǽ- -!");
	DrawString(10,i++,"������ͨʳ��Ե�һ����һ��");
	DrawString(10,i++,"��߷�ʳ��Ե�һ������֣�ÿ��5����ͨʳ��Ż������");
	i=21;
	DrawString(13,i++,"-- �����������ʼ��Ϸ --");
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
		DrawString(1,1,"�����,���������.");

		_getch();
		Start();

		return;
	}

	SnakeEatFood();
}

bool CMyView::HandleMessage()
{
	//���·��ַ������������224
	if (_getch() == 224)
	{
		int ch = _getch();
		switch (ch)
		{
		case 72: //��
			return m_snake.ChangeDirection(direct_up);
		case 77: //��
			return m_snake.ChangeDirection(direct_right);
		case 80: //��
			return m_snake.ChangeDirection(direct_down);
		case 75: //��
			return m_snake.ChangeDirection(direct_left);
		}
	}
	
	return false;
}