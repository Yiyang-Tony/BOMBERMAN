#pragma once
#include "Maze.h"

enum Forward { top = 1, bottom = 3, left = 4, right = 2 };//方向
class Monster
{
public:
	Monster();
	Monster(int x, int y, Maze* mazes);//随机一个怪物的产生位置
	virtual ~Monster();
	Maze* maze;
	void Move();//怪物移动
	bool collisonCheck(int);
	bool borderCheck(int x, int y);

	int m_x, m_y, m_forWard;//怪物出现的位置
	bool alive;
};