#pragma once

class CFood
{
public:
	CFood(int reward = 0);
public: //接口
	int getReward()const {return m_reward;}
	void setPosition(const POINT &pos) {m_ptPos = pos;}
	POINT getPosition()const {return m_ptPos;}
	void ZeroAppearCount() {m_cAppear = 0;}
	void InitialFood();
public: //接口 虚函数
	virtual void Display(bool flag);
	virtual bool IsTimeUp() = 0;
protected:
	int m_reward;
	POINT m_ptPos;
	int m_cAppear; //出现时间计数
};