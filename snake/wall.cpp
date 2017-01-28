#include "stdafx.h"
#include "wall.h"
#include "head.h"

void CWall::InitialWall()
{
	//����
	for (int i = 0;i != MAX_COLS/2+1;++i)
	{
		DrawString(i,0,"��");
		DrawString(i,MAX_LINES-1,"��");
	}

	//����
	for (int i = 0;i != MAX_LINES;++i)
	{
		DrawString(0,i,"��");
		DrawString(MAX_COLS/2-1,i,"��");
	}
}

bool CWall::HitWall(const POINT &pt)
{
	if (   pt.x == 0 || pt.x == MAX_COLS/2-1
		|| pt.y == 0 || pt.y == MAX_LINES-1)
		return true;

	return false;
}