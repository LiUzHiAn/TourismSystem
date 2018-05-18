#pragma once
#include"Graph.h"
#include<fstream>

class Tourism
{
private:
	Graph mGraph;    // ͼ��Ϣ
public:
	Tourism();
	~Tourism();
	bool createGraph();			// ����ͼ
	void querySpotInfo();		// ��ѯ������Ϣ
	void travelPath();			// �õ�����·�� 
	void findShortPath();		// ��ѯ�������֮������·��
	void designPath();			// ��Ƶ�·���ߣ�prim�㷨��
};

