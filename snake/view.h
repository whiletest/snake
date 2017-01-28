#pragma once

#include "wall.h"
#include "snake.h"
#include "food.h"
#include "head.h"

class CMyView
{
public:
	CMyView(HWND hwnd = 0);
	~CMyView();
public:
	void InitialGui();
	void Start();
	void Display();
	bool HandleMessage();
protected:
	void ShowScore();
	void InitialFood();
	void SnakeEatFood();
	void CreateFood(int type); //type=0 ��ͨʳ��,type=1����ʳ��
protected:
	HWND m_hwnd;
	CWall m_wall;
	CSnake m_snake;
	CFood *m_pFood[MAX_NUM_FOOD_APPEAR]; //[0]ָ����ͨʳ��,[1]ָ������ʳ��
	int m_score;
	int m_cToCreateSF; //�Ѿ�������ͨʳ��ļ������Բ�������ʳ��
};