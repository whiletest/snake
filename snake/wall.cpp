#include "stdafx.h"
#include "wall.h"
#include "head.h"

void CWall::InitialWall()
{
	//ÉÏÏÂ
	for (int i = 0;i != MAX_COLS/2+1;++i)
	{
		DrawString(i,0,"¡ñ");
		DrawString(i,MAX_LINES-1,"¡ñ");
	}

	//×óÓÒ
	for (int i = 0;i != MAX_LINES;++i)
	{
		DrawString(0,i,"¡ñ");
		DrawString(MAX_COLS/2-1,i,"¡ñ");
	}
}

bool CWall::HitWall(const POINT &pt)
{
	if (   pt.x == 0 || pt.x == MAX_COLS/2-1
		|| pt.y == 0 || pt.y == MAX_LINES-1)
		return true;

	return false;
}