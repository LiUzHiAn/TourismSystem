#include "Graph.h"
#include<iostream>
#include<vector>
using namespace std;

void Graph::initGraph()
{
	for (int i = 0;i < MAX_SPOT_NUM;i++)
	{
		for (int j = 0;j < MAX_SPOT_NUM;j++)
		{
			// 初始化邻接矩阵为-1，表示所有顶点之间不存在边
			adjMatrix[i][j] = -1;
		}
	}
	// 初始化点个数为0
	vexNum = 0;
	// 初始化边个数为0
	edgeNum = 0;
}

bool Graph::insertVex(Vex vex)
{
	if(vexNum==MAX_SPOT_NUM)
		return false;
	vexs[vexNum++] = vex;
	return true;
}

bool Graph::insertEdge(Edge edge)
{
	if (edge.vex1 < 0 || edge.vex2 < 0 || edge.vex1 >= MAX_SPOT_NUM || edge.vex2 >= MAX_SPOT_NUM)
	{
		cout << "边信息下边越界！" << endl;
		return false;
	}
	// 插入边信息
	adjMatrix[edge.vex1][edge.vex2] = edge.distance;
	adjMatrix[edge.vex2][edge.vex1] = edge.distance;
	edgeNum++;
	return true;
}

Vex Graph::getVex(int vexIndex)
{
	return vexs[vexIndex];
}

int Graph::findEdge(int vexIndex, Edge aEdge[])
{
	int k = 0;
	for (int i = 0;i < vexNum;i++)
	{
		// 在邻接矩阵里面找与vexIndex相邻的边
		if (adjMatrix[vexIndex][i] != -1)  // 有边
		{
			aEdge[k].vex1 = vexIndex;
			aEdge[k].vex2 = i;
			aEdge[k].distance = adjMatrix[vexIndex][i];
			k++;
		}
	}
	return k;
}

int Graph::getVexNum()
{
	return vexNum;
}
 
int Graph::getEdgeNum()
{
	return edgeNum;
}

void Graph::prinGraphInfo()
{ 
	printNodeInfo();  // 打印景点信息
	printEdgeInfo();  // 打印边的信息
}

void Graph::printNodeInfo()
{
	cout << "\n========顶点========" << endl;
	cout << "顶点数目:" << vexNum << endl;
	for (int i = 0;i < vexNum;i++)
	{
		cout << getVex(i).num << "--" << getVex(i).spotName << "--" << getVex(i).spotInfo << endl;
	}
	cout << endl;
}

void Graph::printEdgeInfo()
{
	cout << "========边=========" << endl;
	for (int i = 0;i < vexNum;i++)
	{
		for (int j = i;j < vexNum;j++)
		{
			if (adjMatrix[i][j] != -1)
			{
				cout << "<V" << i << ",V" << j << "> -->" << adjMatrix[i][j] << "米" << endl;
			}
		}
	}
	cout << endl;
}

void Graph::DFS(int beginVexIndex, bool visited[], int & depth, PathList &pathList)
{
	
	visited[beginVexIndex] = true;
	pathList->vexIndex[depth] = beginVexIndex;  // 当前深度下对应访问当前结点
	// 是否所有点都被走过
	if (true == allVisited(visited, vexNum))
	{
		// 新建一个路径结点
		PathNode *newNode = new PathNode;
		newNode->next = NULL;
		// 将回溯位置前的值全部记下
		for (int i = 0;i < vexNum;i++)
		{
			newNode->vexIndex[i] = pathList->vexIndex[i];
		}
		// 链表头为新建结点的下一个
		pathList->next = newNode;
		pathList = newNode;
	}
	for(int i=0;i<vexNum;i++)
	{
		// 与当前结点有边且没被访问过
		if (adjMatrix[beginVexIndex][i] != -1&&visited[i]==false)
		{
			depth++; // 下一层
			DFS(i, visited, depth, pathList);
			visited[i] = false;
			depth--;
		}
	}

}

bool Graph::allVisited(bool visited[],int num)
{
	for (int i = 0;i < num;i++)
	{
		//  只要有一个还没被访问，就返回false
		if (false == visited[i])
			return false;
	}
	return true;
}

void Graph::DFSTravel(int beginVexIndex, PathList &pathList)
{
	int depth = 0;
	bool visited[MAX_SPOT_NUM] = { false };
	DFS(beginVexIndex, visited, depth,pathList);
}

void Graph::findShortPath(int vexStart, int vexEnd, Edge pathEdges[])
{
	bool visited[MAX_SPOT_NUM] = { false };
	int weight[MAX_SPOT_NUM];
	// 初始化长度数组为无穷
	for (int i = 0;i < vexNum;i++)
	{
		weight[i] = INT_MAX;
	}

	// 起点到起点的路径为0
	weight[vexStart] = 0;
	visited[vexStart] = true;
	pathEdges[vexStart].vex1 = vexStart;
	pathEdges[vexStart].vex2 = vexStart;
	pathEdges[vexStart].distance = 0;

	// 初始化长度数组为start为起点的情况
	for (int i = 0;i < vexNum;i++)
	{
		if (adjMatrix[vexStart][i]!=-1)
		{
			weight[i] = adjMatrix[vexStart][i];
			// 结点i的前驱为源点
			pathEdges[i].vex1 = vexStart;
			// vex2没什么意义
			pathEdges[i].vex2 = i;
			pathEdges[i].distance = adjMatrix[vexStart][i];
		}
	}
	// 最短路径对应的点下标
	int minIndex = -1;
	// 已经走过的点数
	int vexVisitedNum = 1;

	while(vexVisitedNum != vexNum)
	{ 
		// 找到当前长度数组中最小的那个
		int min = INT_MAX;
		
		for(int i=0;i<vexNum;i++)
		{
			 // 每访问过的中找最小的
			if (visited[i]==false && weight[i] < min)
			{
				min = weight[i];
				minIndex = i;
			}
		}
		// 访问与当前点长度最小的点
		visited[minIndex] = true;
		vexVisitedNum++;

		// 根据最小的中转点，相应修改长度数组
		for(int j=0;j<vexNum;j++)
		{
			// 如果另一个点没被访问且与当前中转点有边，并且经过中转后的长度和比原来更小
			if ((adjMatrix[minIndex][j] + weight[minIndex] < weight[j])&&(visited[j] == false) && (adjMatrix[minIndex][j] != -1))
			{
				weight[j] = adjMatrix[minIndex][j] + weight[minIndex];
				// 更新结点的前驱
				pathEdges[j].vex1 = minIndex;
				pathEdges[j].vex2 = j;
				pathEdges[j].distance = weight[j];
			}
		}
	}
}

vector<Edge> Graph::findMinTree()
{
	vector<Edge> edgesVec;
	Edge newEdge;
	int adjvex[MAX_SPOT_NUM];	// 相关顶点下标
	int lowcost[MAX_SPOT_NUM];  // 动态保存最短边数组
	// 这里假设从v0结点开始找
	lowcost[0] = 0;			// lowcost=0表示已经加入生成树
	adjvex[0] = 0;
	for (int i = 1;i < vexNum;i++)
	{
		// 如果与生成树中的点有边
		if (adjMatrix[0][i] != -1)
		{
			lowcost[i] = adjMatrix[0][i];
			adjvex[i] = 0;
		}
		else
		{
			lowcost[i] = INT_MAX;
			adjvex[i] = 0;
		}
			
	}
	// 循环所有点
	for (int i = 1;i < vexNum;i++)
	{

		int min = INT_MAX;
		int minIndex = -1;
		// 找最小边
		for (int j = 1;j < vexNum;j++)
		{
			// 如果结点没加入生成树且比最小路径还短
			if ((lowcost[j] != 0) && lowcost[j] < min)
			{
				min = lowcost[j];
				minIndex = j;
			}
		}
		// 最小边对应的点加入生成树
		lowcost[minIndex] = 0;
		// 添加新的边到边集向量中
		newEdge.vex1 = adjvex[minIndex];
		newEdge.vex2 = minIndex;
		newEdge.distance=min;
		edgesVec.push_back(newEdge);
		// 更新最小边
		for (int i = 1;i < vexNum;i++)
		{
			// 点没访问过，且边长比当前值还小
			if (lowcost[i] != 0 && (adjMatrix[minIndex][i]!=-1)&&adjMatrix[minIndex][i] < lowcost[i])
			{
				lowcost[i] = adjMatrix[minIndex][i];
				adjvex[i] = minIndex;
			}
		}
		
	}
	return edgesVec;
}
