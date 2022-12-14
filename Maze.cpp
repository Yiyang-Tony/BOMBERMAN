// Maze.cpp : implementation file
//

#include "stdafx.h"
#include "BOMBERMAN.h"
#include "Maze.h"

#include"gl/gl.h"
#include"gl/glu.h"



// Maze

Maze::Maze()
{
	play_x = play_y = 0;
	play_forward = playerDown1;
	initMaze();
}

Maze::~Maze()
{

}


//绘制迷宫
void Maze::DrawMaze(void)
{

	//设置清屏颜色为黑色
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//清除颜色缓冲区和深度缓冲区
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0, 0, -100);
	glRotatef(180, 1, 0, 0);
	glTranslatef(-WINDOWWIDTH / 13, -WINDOWHEIGHT / 15, 0);

	CPoint p,player;
	for (int i = 0; i < MAZEROW; i++)
	{
		for (int j = 0; j < MAZECOL; j++) {
			p.x = j * CELLWIDTH;
			p.y = i * CELLHEIGHT;
			if ((ppMaze[i][j] >= playerUp && ppMaze[i][j] <= playerLeft)|| (ppMaze[i][j] >= playerWboomUp && ppMaze[i][j] <= playerWboomLeft)) {
				player = p;
				drawCell(p, normal);
			}
			else {
				drawCell(p, normal);
				drawCell(p, ppMaze[i][j]);
			}
		}
	}

	drawPlayer(player.x, player.y);
	glFlush();
	SwapBuffers(wglGetCurrentDC());
}



//初始化迷宫
void Maze::initMaze() {
	int i, j;
	gameOver = false;
	memset(ppMaze, normal, sizeof(ppMaze));//0代表可以通过的路径
	for (i = 1; i < MAZEROW; i += 2)
	{
		for (j = 1; j < MAZECOL; j += 2) {

			ppMaze[i][j] = obstacle;
		}
	}
	ppMaze[0][0] = playerDown;//设置玩家
	createBrick();//随机生成砖块
}

//随机生成砖块
void Maze::createBrick()
{
	srand((unsigned)time(NULL));
	for (int i = 0; i < MAZEROW; i += 2)
	{
		for (int j = 0; j < MAZECOL; j += 2) {
			if (i == 0 && j == 0)
				continue;
			if (rand() % 8 < 5)
				ppMaze[i][j] = brick;
		}
	}

}


//绘制方格, 在p位置绘制type方格
void Maze::drawCell(CPoint p, int type)
{
	
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, Texture[type].ID);
	glBegin(GL_QUADS);  // OpenGL绘制直线命令
	glTexCoord2f(0.0f, 1.0f); glVertex2d(p.x, p.y);
	glTexCoord2f(1.0f, 1.0f); glVertex2d(p.x + CELLWIDTH, p.y);
	glTexCoord2f(1.0f, 0.0f); glVertex2d(p.x + CELLWIDTH, p.y + CELLHEIGHT);
	glTexCoord2f(0.0f, 0.0f); glVertex2d(p.x, p.y + CELLHEIGHT);
	glEnd();
	glPopMatrix();

}
//绘制玩家, 在p位置绘制
void Maze::drawPlayer(float x, float y)
{
	if (isStop)
		glBindTexture(GL_TEXTURE_2D, Texture[play_forward].ID);
	else {
		count++;
		glBindTexture(GL_TEXTURE_2D, Texture[play_forward + count].ID);
	}
	if (count == 4) {
		isStop = true;
	}
	glBegin(GL_QUADS);  // OpenGL绘制直线命令
	glTexCoord2f(0.0f, 1.0f); glVertex2d(x - play_x * CELLWIDTH * (4 - count), y - play_y * CELLHEIGHT* (4 - count));
	glTexCoord2f(1.0f, 1.0f); glVertex2d(x - play_x * CELLWIDTH * (4 - count) + CELLWIDTH, y - play_y * CELLHEIGHT* (4 - count));
	glTexCoord2f(1.0f, 0.0f); glVertex2d(x - play_x * CELLWIDTH * (4 - count) + CELLWIDTH, y + CELLHEIGHT - play_y * CELLHEIGHT*(4 - count));
	glTexCoord2f(0.0f, 0.0f); glVertex2d(x - play_x * CELLWIDTH * (4 - count), y + CELLHEIGHT - play_y * CELLHEIGHT* (4 - count));
	glEnd();

}
//设置幻方值
void Maze::setCellVal(int x, int y, int val)
{
	ppMaze[x][y] = val;
}

//得到幻方值
int Maze::getCellVal(int x, int y)
{
	return ppMaze[x][y];
}
