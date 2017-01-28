#include "stdafx.h"
#include "snake.h"
#include "head.h"

CSnake::CSnake():m_pHead(0),
                 m_pTail(0),
				 m_speed(1)
{
	
}

CSnake::~CSnake()
{
	if (m_pHead)
	{
		SNAKE_NODE *pTem = m_pHead->pNext;
		while (pTem)
		{
			m_pHead->pNext = pTem->pNext;
			delete pTem;
			pTem = m_pHead->pNext;
		}
		delete m_pHead;
	}
}

void CSnake::InitialSnake()
{
	POINT ptHead = {MAX_COLS/4,MAX_LINES/2};
	int nodeCount = 4;

	m_pHead = m_pTail = new SNAKE_NODE;
	m_pHead->ptPos = ptHead;
	m_pHead->direction = direct_up;
	DrawString(m_pHead->ptPos.x,m_pHead->ptPos.y,"◎");
	
	SNAKE_NODE *pTem  = 0;
	while (nodeCount--)
	{
		pTem = new SNAKE_NODE;
		pTem->direction = m_pTail->direction;
		pTem->ptPos.x = m_pTail->ptPos.x;
		pTem->ptPos.y = m_pTail->ptPos.y + 1;
		pTem->pNext = 0;
		DrawString(pTem->ptPos.x,pTem->ptPos.y,"◎");

		m_pTail->pNext = pTem;
		m_pTail = pTem;
	}
}

bool CSnake::ChangeDirection(_direction dir)
{
	//不能直接反方向
	if (   m_pHead->direction - dir == 1
		|| m_pHead->direction - dir == -1)
		return false;

	//不同方向时
	if (m_pHead->direction != dir)
	{
		m_pHead->direction = dir;
		return true;
	}

	return false;
}

void CSnake::MoveNode()
{
	if (m_pHead)
	{
		POINT ptPrev = m_pHead->ptPos;

		switch (m_pHead->direction)
		{
		case direct_up:
			m_pHead->ptPos.y -= m_speed;
			break;
		case direct_down:
			m_pHead->ptPos.y += m_speed;
			break;
		case direct_left:
			m_pHead->ptPos.x -= m_speed;
			break;
		case direct_right:
			m_pHead->ptPos.x += m_speed;
			break;
		}

		SNAKE_NODE *pTem = m_pHead->pNext;
		POINT ptTem = {0};
		while(pTem)
		{
			ptTem = pTem->ptPos;
			pTem->ptPos = ptPrev;
			ptPrev = ptTem;
			pTem = pTem->pNext;
		}
	}
}

void CSnake::Move()
{
	DrawString(m_pTail->ptPos.x,m_pTail->ptPos.y," ");

	MoveNode();

	DrawString(m_pHead->ptPos.x,m_pHead->ptPos.y,"◎");
}

int CSnake::IsEatFood(const CFood *pFood)
{
		POINT posFood = pFood->getPosition();
		bool bEatFood = false;

		switch (m_pHead->direction)
		{
		case direct_down:
			if (   m_pHead->ptPos.y == posFood.y-m_speed
				&& m_pHead->ptPos.x == posFood.x)
			{
				bEatFood = true;
			}
			break;
		case direct_left:
			if (   m_pHead->ptPos.y == posFood.y
				&& m_pHead->ptPos.x == posFood.x+m_speed)
			{
				bEatFood = true;
			}
			break;
		case direct_right:
			if (   m_pHead->ptPos.y == posFood.y
				&& m_pHead->ptPos.x == posFood.x-m_speed)
			{
				bEatFood = true;
			}
			break;
		case direct_up:
			if (   m_pHead->ptPos.y == posFood.y+m_speed
				&& m_pHead->ptPos.x == posFood.x)
			{
				bEatFood = true;
			}
			break;
		}

		if (bEatFood)
		{
			SNAKE_NODE *pTemNode = new SNAKE_NODE;
			pTemNode->ptPos = posFood;
			pTemNode->direction = m_pHead->direction;
			pTemNode->pNext = m_pHead;
			m_pHead = pTemNode;
			DrawString(m_pHead->ptPos.x,m_pHead->ptPos.y,"◎");

			return pFood->getReward();
		}
		
	return 0;
}

bool CSnake::IsEatSelf()
{
	if (m_pHead)
	{
		SNAKE_NODE *pTemNode = m_pHead->pNext;
		while(pTemNode)
		{
			if (   m_pHead->ptPos.x == pTemNode->ptPos.x
				&& m_pHead->ptPos.y == pTemNode->ptPos.y)
				return true;

			pTemNode = pTemNode->pNext;
		}
	}

	return false;
}