#include "stdafx.h"
#include "Monster.h"

Monster::Monster()
{
}


Monster::~Monster()
{
}
//怪物移动
void Monster::Move() {
	int n_x = m_x, n_y = m_y;

	srand((unsigned)time(NULL));
	switch (rand() %4+1)
	{
	case top:
		m_forWard = top;
		n_x--;
		break;
	case right:
		m_forWard = right;
		n_y++;
		break;
	case bottom:
		m_forWard = bottom;
		n_x++;
		break;
	case left:
		m_forWard = left;
		n_y--;
		break;
	default:
		break;
	}

	int tvalue = maze->getCellVal(n_x, n_y);

	if (!borderCheck(n_x, n_y) || !collisonCheck(tvalue))
		return;


	maze->setCellVal(m_x, m_y, normal);

	m_x = n_x, m_y = n_y;
	maze->setCellVal(m_x, m_y, 40 + m_forWard);

	if (tvalue >= playerUp && tvalue <= playerLeft)
	{
		maze->gameOver = true;
	}

}
//初始化怪物生成位置
Monster::Monster(int x,int y, Maze* mazes)
{
	m_forWard = bottom;
	m_x = x;
	m_y = y;
	alive = true;
	maze = mazes;
}

//边界检查
bool Monster::borderCheck(int x, int y) {
	if (x<0 || x>MAZEROW - 1 || y<0 || y>MAZECOL - 1)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool Monster::collisonCheck(int val)
{
	if (val >= playerUp && val <= playerLeft)
	{
		return true;
	}
	if (val == normal)
	{
		return true;
	}
	else
	{
		return false;
	}
}

