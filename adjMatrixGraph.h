#include "graph.h"
#include "DisjointSet.h"
#include <iostream>
#include <stdlib.h>
#include <queue>

template <typename TypeOfVer, typename TypeOfEdge>
class adjMatrixGraph :public graph<TypeOfEdge>
{
public:
	adjMatrixGraph(int vSize, const TypeOfVer d[], const TypeOfEdge noEdgeFlag);
	bool insert(int u, int v, TypeOfEdge w);
	bool remove(int u, int v);
	bool exist(int u, int v)const;
	void dfs()const;
	void bfs()const;
	void EulerCircuit(TypeOfVer start);
	void kruskal()const;
	void prim()const;
	void floyd()const;
	void dfsTopSort()const;
	~adjMatrixGraph();
private:
	struct edgeNode
	{
		int beg, end;
		TypeOfEdge w;
		bool operator <(const edgeNode &rp)const { return w < rp.w; }
	};
	struct EulerNode
	{
	    int NodeNum;
	    EulerNode *next;
	    EulerNode(int ver){NodeNum=ver;next=nullptr;}
	};
	TypeOfEdge **edge;
	TypeOfVer *ver;
	TypeOfEdge noEdge;

	void dfs(int start, bool visited[])const;
	void dfsTopSort(int start, bool visited[])const;
	void EulerCircuit(int start, EulerNode *&beg, EulerNode *&end, int numOfDegree[]);
	TypeOfEdge **clone();
};

template <typename TypeOfVer, typename TypeOfEdge>
adjMatrixGraph<TypeOfVer, TypeOfEdge>::adjMatrixGraph(int vSize, const TypeOfVer d[], TypeOfEdge noEdgeFlag)
{
	int i, j;
	graph<TypeOfEdge>::Vers = vSize;
	graph<TypeOfEdge>::Edges = 0;
	noEdge = noEdgeFlag;

	//存放结点的数组初始化
	ver = new TypeOfVer[vSize];
	for (i = 0;i < vSize;++i)
		ver[i] = d[i];
	//邻接矩阵的初始化
	edge = new TypeOfEdge *[vSize];
	for (i = 0;i < vSize;++i)
	{
		edge[i] = new TypeOfEdge[vSize];
		for (j = 0;j < vSize;++j)
			edge[i][j] = noEdge;
		edge[i][i] = 0;
	}
}

template <typename TypeOfVer, typename TypeOfEdge>
adjMatrixGraph<TypeOfVer, TypeOfEdge>::~adjMatrixGraph()
{
	delete[]ver;
	for (int i = 0;i < graph<TypeOfEdge>::Vers;++i)delete[]edge[i];//释放邻接矩阵中的每一行
	delete[]edge;
}

template <typename TypeOfVer, typename TypeOfEdge>
bool adjMatrixGraph<TypeOfVer, TypeOfEdge>::insert(int u, int v, TypeOfEdge w)
{
	if (u<0 || u>graph<TypeOfEdge>::Vers - 1 || v<0 || v>graph<TypeOfEdge>::Vers - 1)
		return false;
	if (edge[u][v] != noEdge)
		return false;
	edge[u][v] = w;
	++graph<TypeOfEdge>::Edges;
	return true;
}

template <typename TypeOfVer, typename TypeOfEdge>
bool adjMatrixGraph<TypeOfVer, TypeOfEdge>::remove(int u, int v)
{
	if (u < 0 || u>graph<TypeOfEdge>::Vers - 1 || v<0 || v>graph<TypeOfEdge>::Vers - 1)
		return false;
	if (edge[u][v] == noEdge)
		return false;
	edge[u][v] = noEdge;
	--graph<TypeOfEdge>::Edges;
	return true;
}

template <typename TypeOfVer, typename TypeOfEdge>
bool adjMatrixGraph<TypeOfVer, TypeOfEdge>::exist(int u, int v)const
{
	if (u<0 || u>graph<TypeOfEdge>::Vers - 1 || v<0 || v>graph<TypeOfEdge>::Vers - 1)
		return false;
	if (edge[u][v] == noEdge)
		return false;
	else
		return true;
}

template <typename TypeOfVer, typename TypeOfEdge>
void adjMatrixGraph<TypeOfVer, TypeOfEdge>::dfs()const//公有的dfs
{
	int i;
	bool *visited = new bool[graph<TypeOfEdge>::Vers];
	for (i = 0;i < graph<TypeOfEdge>::Vers;++i)visited[i] = false;
	std::cout << "当前图的深度优先遍历序列为：" << std::endl;

	for (i = 0;i < graph<TypeOfEdge>::Vers;++i)
	{
		if (visited[i] == true)continue;
		dfs(i, visited);
		std::cout << std::endl;
	}
}

template <typename TypeOfVer, typename TypeOfEdge>
void adjMatrixGraph<TypeOfVer, TypeOfEdge>::dfs(int start, bool visited[])const//私有的dfs
{
	std::cout << ver[start] << '\t';//访问结点
	visited[start] = true;

	for (int i = 0;i < graph<TypeOfEdge>::Vers;++i)//深度优先遍历start后继
	{
		if (edge[start][i] != noEdge&&!visited[i])
			dfs(i, visited);
	}
}

template <typename TypeOfVer, typename TypeOfEdge>
void adjMatrixGraph<TypeOfVer, TypeOfEdge>::bfs()const
{
	bool *visited = new bool[graph<TypeOfEdge>::Vers];
	int currentNode;
	std::queue<int>q;
	int i, j;

	for (i = 0;i < graph<TypeOfEdge>::Vers;++i)visited[i] = false;

	std::cout << "当前图的广度优先遍历序列为：" << std::endl;

	for (i = 0;i < graph<TypeOfEdge>::Vers;++i)
	{
		if (visited[i])continue;
		q.push(i);
		while (!q.empty())
		{
			currentNode = q.front();
			q.pop();
			if (visited[currentNode])continue;
			std::cout << ver[currentNode] << '\t';
			visited[currentNode] = true;
			for (j = 0;j < graph<TypeOfEdge>::Vers;++j)
				if (edge[currentNode][j] != noEdge&&!visited[j])
					q.push(i);
		}
		std::cout << std::endl;
	}
}

template <typename TypeOfVer, typename TypeOfEdge>
void adjMatrixGraph<TypeOfVer, TypeOfEdge>::EulerCircuit(TypeOfVer start)
{
	EulerNode *beg, *end, *p, *q, *tb, *te;
	int *numOfDegree = new int[graph<TypeOfEdge>::Vers], i, j;
	TypeOfEdge **tmp;

	if (graph<TypeOfEdge>::Edges < graph<TypeOfEdge>::Vers - 1)
	{
		std::cout << "不存在欧拉回路" << std::endl;
		return;
	}
	for (i = 0;i < graph<TypeOfEdge>::Vers;++i)
	{
		numOfDegree[i] = 0;
		for (j = 0;j < graph<TypeOfEdge>::Vers;++j)
			if (edge[i][j] != noEdge)
				++numOfDegree[i];
		if (numOfDegree[i] == 0 || numOfDegree[i] % 2)
		{
			std::cout << "不存在欧拉回路" << std::endl;
			return;
		}
	}

	for (i = 0;i < graph<TypeOfEdge>::Vers;++i)
		if (ver[i] == start)
			break;

	if (i == graph<TypeOfEdge>::Vers)
	{
		std::cout << "起始结点不存在" << std::endl;
		return;
	}
	tmp = clone();

	EulerCircuit(i, beg, end, numOfDegree);
	while (true)
	{
		p = beg;
		while (p->next != nullptr)
			if (numOfDegree[p->next->NodeNum] != 0)
				break;
			else p = p->next;
		if (p->next == nullptr)
			break;
		q = p->next;
		EulerCircuit(q->NodeNum, tb, te, numOfDegree);
		te->next = q->next;
		p->next = tb;
		delete q;
	}

	delete[]edge;
	edge = tmp;

	std::cout << "欧拉回路是：" << std::endl;
	while (beg != nullptr)
	{
		std::cout << ver[beg->NodeNum] << '\t';
		p = beg;beg = beg->next;
		delete p;
	}
	std::cout << std::endl;
}

template <typename TypeOfVer, typename TypeOfEdge>
void adjMatrixGraph<TypeOfVer, TypeOfEdge>::EulerCircuit(int start, EulerNode *&beg, EulerNode *&end, int numOfDegree[])
{
	int nextNode;

	beg = end = new EulerNode(start);
	while (numOfDegree[start] != 0)
	{
		for (nextNode = 0;nextNode < graph<TypeOfEdge>::Vers;++nextNode)
			if (edge[start][nextNode] != noEdge)
				break;
		remove(start, nextNode);
		remove(nextNode, start);
		--numOfDegree[start];
		--numOfDegree[nextNode];
		start = nextNode;
		end->next = new EulerNode(start);
		end = end->next;
	}
}

template <typename TypeOfVer, typename TypeOfEdge>
TypeOfEdge **adjMatrixGraph<TypeOfVer, TypeOfEdge>::clone()
{
	TypeOfEdge **tmp = new TypeOfEdge *[graph<TypeOfEdge>::Vers];
	int i, j;
	for (i = 0;i < graph<TypeOfEdge>::Vers;++i)
	{
		tmp[i] = new TypeOfEdge[graph<TypeOfEdge>::Vers];
		for (j = 0;j < graph<TypeOfEdge>::Vers;++j)
			tmp[i][j] = edge[i][j];
	}
	return tmp;
}

template <typename TypeOfVer,typename TypeOfEdge>
void adjMatrixGraph<TypeOfVer, TypeOfEdge>::kruskal()const
{
	int edgesAccepted = 0;
	int u, v, i, j;
	DisjointSet ds(graph<TypeOfEdge>::Vers);
	std::priority_queue<edgeNode>pq;
	edgeNode e;

	for (i = 0;i < graph<TypeOfEdge>::Vers;++i)
	{
		for (j = 0;j < graph<TypeOfEdge>::Vers;++j)
			if (edge[i][j] != noEdge)
			{
				e.beg = i;
				e.end = j;
				e.w = edge[i][j];
				pq.push(e);
			}
	}
	while (edgesAccepted < graph<TypeOfEdge>::Vers - 1)
	{
		e = pq.top();pq.pop();
		u = ds.Find(e.beg);
		v = ds.Find(e.end);
		if (u != v)
		{
			edgesAccepted++;
			ds.Union(u, v);
			std::cout << '(' << ver[e.beg] << ',' << ver[e.end] << ")\t";
		}
	}
}

template <typename TypeOfVer, typename TypeOfEdge>
void adjMatrixGraph<TypeOfVer, TypeOfEdge>::prim()const
{
	bool *flag = new bool[graph<TypeOfEdge>::Vers];
	TypeOfEdge *lowCost = new TypeOfEdge[graph<TypeOfEdge>::Vers];
	int *startNode = new int[graph<TypeOfEdge>::Vers];
	TypeOfEdge min;
	int start, i, j;

	for (i = 0;i < graph<TypeOfEdge>::Vers;++i)
	{
		flag[i] = false;
		lowCost[i] = noEdge;
	}
	start = 0;
	for (i = 1;i < graph<TypeOfEdge>::Vers;++i)
	{
		for (j = 0;j < graph<TypeOfEdge>::Vers;++j)
		{
			if (!flag[j] && lowCost[j]>edge[start][j])
			{
				lowCost[j] = edge[start][j];
				startNode[j] = start;
			}
		}
		flag[start] = true;
		min = noEdge;
		for (j = 0;j < graph<TypeOfEdge>::Vers;++j)
		{
			if (lowCost[j] < min)
			{
				min = lowCost[j];
				start = j;
			}
		}
		std::cout << '(' << ver[startNode[start]] << ',' << ver[start] << ")\t";
		lowCost[start] = noEdge;
	}
	delete[]flag;
	delete[]startNode;
	delete[]lowCost;
}

template <typename TypeOfVer, typename TypeOfEdge>
void adjMatrixGraph<TypeOfVer, TypeOfEdge>::floyd()const
{
	TypeOfEdge **d = new TypeOfEdge *[graph<TypeOfEdge>::Vers];
	int **prev = new int *[graph<TypeOfEdge>::Vers];
	int i, j, k;

	for (i = 0;i < graph<TypeOfEdge>::Vers;++i)
	{
		d[i] = new TypeOfEdge[graph<TypeOfEdge>::Vers];
		prev[i] = new int[graph<TypeOfEdge>::Vers];
		for (j = 0;j < graph<TypeOfEdge>::Vers;++j)
		{
			d[i][j] = edge[i][j];
			prev[i][j] = (edge[i][j] != noEdge) ? i : -1;
		}
	}
	for (k = 0;k < graph<TypeOfEdge>::Vers;++k)
		for (i = 0;i < graph<TypeOfEdge>::Vers;++i)
			for (j = 0;j < graph<TypeOfEdge>::Vers;++j)
				if (d[i][k] + d[j][k] < d[i][j])
				{
					d[i][j] = d[i][k] + d[i][j];
					prev[i][j] = prev[k][j];
				}
	std::cout << "最短路径长度：" << std::endl;
	for (i = 0;i < graph<TypeOfEdge>::Vers;++i)
	{
		std::cout << std::endl;
		for (j = 0;j < graph<TypeOfEdge>::Vers;++j)
			std::cout << d[i][j] << '\t';
	}

	cout << endl;
	std::cout << "最短路径：" << std::endl;
	for (i = 0;i < graph<TypeOfEdge>::Vers;++i)
	{
		std::cout << std::endl;
		for (j = 0;j < graph<TypeOfEdge>::Vers;++j)
			std::cout << prev[i][j] << '\t';
	}
}

template <typename TypeOfVer, typename TypeOfEdge>
void adjMatrixGraph<TypeOfVer, TypeOfEdge>::dfsTopSort()const//公有的dfsTopSort
{
	int i;
	bool *visited = new bool[graph<TypeOfEdge>::Vers];
	for (i = 0;i < graph<TypeOfEdge>::Vers;++i)visited[i] = false;
	std::cout << "当前图的拓扑排序的逆序为：" << std::endl;

	for (i = 0;i < graph<TypeOfEdge>::Vers;++i)
	{
		if (visited[i] == true)continue;
		dfsTopSort(i, visited);
		//std::cout << std::endl;
	}
}

template <typename TypeOfVer, typename TypeOfEdge>
void adjMatrixGraph<TypeOfVer, TypeOfEdge>::dfsTopSort(int start, bool visited[])const//私有的dfsTopSort
{
	visited[start] = true;

	for (int i = 0;i < graph<TypeOfEdge>::Vers;++i)//深度优先遍历start后继
	{
		if (edge[start][i] != noEdge&&!visited[i])
			dfsTopSort(i, visited);
	}
	std::cout << ver[start] << '\t';//访问结点
}