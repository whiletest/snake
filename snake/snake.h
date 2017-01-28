#pragma once

#include "food.h"

enum _direction
{
	direct_up,
	direct_down,
	direct_left = 3,
	direct_right
};

struct SNAKE_NODE
{
	POINT ptPos;
	_direction direction; //������head
	SNAKE_NODE *pNext;
};

class CSnake
{
public:
	CSnake();
	~CSnake();
public: //�������� �ӿ�
	POINT getHeadPosition()const {return m_pHead->ptPos;}
public: //�ӿ�
	void InitialSnake();
	bool ChangeDirection(_direction dir);
	void Move();
	int IsEatFood(const CFood *pFood);
	bool IsEatSelf();
protected: //˽�к���
	void MoveNode();
protected:
	SNAKE_NODE *m_pHead;
	SNAKE_NODE *m_pTail;
	int m_speed;
};