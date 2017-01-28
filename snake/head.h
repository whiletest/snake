#pragma once

#define MAX_COLS 81
#define MAX_LINES 30

#define MAX_NUM_FOOD_APPEAR 2 //定义最大食物出现个数
#define MAX_TIME_FOOD_APPEAR 50 //定义食物出现最久时间
#define MAX_COUNT_TO_CREATE_SPECIAL_FOOD 5 //定义吃多少个普通食物会产生特殊食物

void DrawString(int x,int y,const char *format,...);