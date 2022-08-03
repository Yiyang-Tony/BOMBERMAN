#pragma once
#include"Maze.h"

class Boom
{
public:
	Boom();
	Boom(int x, int y, int id, int range, double startTimer);//构造函数
	virtual ~Boom();
	int x, y, startTime, rang, boomTime, boomId;//坐标 开始时间 爆炸范围 爆炸时间 id
	void explose(Maze* maze);//爆炸
	bool Boom::eachCase(int x, int y, Maze* maze);//遍历四周是否为空地
	bool timeOver(double time);//判断是否到达爆炸时间
};

