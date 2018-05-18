#pragma once
#include"Graph.h"
#include<fstream>

class Tourism
{
private:
	Graph mGraph;    // 图信息
public:
	Tourism();
	~Tourism();
	bool createGraph();			// 创建图
	void querySpotInfo();		// 查询景点信息
	void travelPath();			// 得到导航路线 
	void findShortPath();		// 查询两个结点之间的最短路径
	void designPath();			// 设计电路布线（prim算法）
};

