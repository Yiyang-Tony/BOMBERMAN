#include "stdafx.h"
#include "Player.h"
#include "Monster.h"

Player::Player()
{
	range = 1;
	n = 0;						//记录炸弹个数
	boomid = 0;
	p_x = p_y = 0;
	p_forWard = bottom;

}

Player::~Player()
{
}
//玩家移动
void Player::move(int key,double time) {
	int n_x = p_x, n_y = p_y;
	
	switch (key)
	{
	case VK_SPACE:
		if (maze->getCellVal(p_x, p_y) != boom) {
			maze->setCellVal(p_x, p_y, 94 + p_forWard);
			bullet = new Boom(p_x, p_y, boomid++, range, time);		//制造炸弹
			boomlist->push_back(bullet);							//放入链表
			point[n++].x = p_x;
			point[n++].y = p_y;
		}
		return;
		break;
	case VK_UP:
		p_forWard = top;
		maze->play_forward = playerUp1;
		n_x--;
		maze->play_x = 0;
		maze->play_y = -0.25;
		break;
	case VK_RIGHT:
		p_forWard = right;
		n_y++;
		maze->play_x = 0.25;
		maze->play_y = 0;
		maze->play_forward = playerRight1;
		break;
	case VK_DOWN:
		p_forWard = bottom;
		n_x++;
		maze->play_x = 0;
		maze->play_y = 0.25;
		maze->play_forward = playerDown1;
		break;
	case VK_LEFT:
		p_forWard = left;
		n_y--;
		maze->play_x = -0.25;
		maze->play_y = 0;
		maze->play_forward = playerLeft1;
		break;
	default:
		break;
	}

	int tvalue = maze->getCellVal(n_x, n_y);
	if (!borderCheck(n_x, n_y) || !collisonCheck(tvalue))
		return;

	if (maze->getCellVal(n_x, n_y) == reward)
		range++;
	

	maze->isStop = false;
	maze->count = 0;

	if (maze->getCellVal(p_x, p_y) >= playerWboomUp
		&& maze->getCellVal(p_x, p_y) <= playerWboomLeft)
	{
		maze->setCellVal(p_x, p_y, boom);
	}
	else
	{
		maze->setCellVal(p_x, p_y, normal);
	}
	 p_x= n_x ,  p_y= n_y ;
	 maze->setCellVal(p_x, p_y, 90 + p_forWard);


	 if (tvalue >= monsterUp && tvalue <= monsterLeft)
	 {
		 maze->gameOver = true;
	 }
}
//边界检查
bool Player::borderCheck(int x, int y) {
	if (x<0 || x>MAZEROW - 1 || y<0 || y>MAZECOL - 1)
	{
		return false;
	}
	else
	{
		return true;
	}
}
//碰撞检测
bool Player::collisonCheck(int val) {

	if (val >= monsterUp && val <= monsterLeft)
	{
		return true;
	}
	if (val == normal || val == reward)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Player::isEnd()
{
	for (int i = 0; i <= n; i++)
		if (abs(p_x - point[i].x) <= range || abs(p_y - point[i].y) <= range)
		{
			if (p_x == p_y == 0)
				continue;
			return true;
		}
		else
		{
			return false;
		}
}