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
	void CreateFood(int type); //type=0 普通食物,type=1特殊食物
protected:
	HWND m_hwnd;
	CWall m_wall;
	CSnake m_snake;
	CFood *m_pFood[MAX_NUM_FOOD_APPEAR]; //[0]指向普通食物,[1]指向特殊食物
	int m_score;
	int m_cToCreateSF; //已经吃了普通食物的计数用以产生特殊食物
};