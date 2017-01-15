#include "graph.h"
#include "DisjointSet.h"
#include "priorityQueueLink.h"
#include <queue>
#include <iostream>
#include <stdlib.h>
#include <algorithm>

template <typename TypeOfVer, typename TypeOfEdge>
class adjListGraph :public graph<TypeOfEdge>
{
public:
	adjListGraph(int vSize, const TypeOfVer d[]);
	bool insert(int u, int v, TypeOfEdge w);
	bool remove(int u, int v);
	bool exist(int u, int v)const;
	void dfs() const;
	void bfs() const;
	void EulerCircuit(TypeOfVer start);
	void topSort() const;//不采用队列实现拓扑排序，
	void queueTopSort() const;
	~adjListGraph();
	void findStrong()const;//找出有向图的所有强通连分量；
	void find(TypeOfVer start, int m)const;//找出从指定结点出发、长度为M 的所有简单路径；
	bool checkRoute(TypeOfVer start, TypeOfVer end)const;//检查图中任意两个结点之间是否存在路径；
	void dfs(TypeOfVer start)const;//增加一个DFS 函数，允许该函数接受一个指定搜索起始位置的参数；
	void bfs(TypeOfVer start)const;//增加一个BFS 函数，允许该函数接受一个指定搜索起始位置的参数；
	bool isDAG()const;//检验一个有向图是否为有向无环图（DAG）；

	void kruskal()const;
	void kruskal(TypeOfVer startVer)const;
	void prim(TypeOfEdge noEdge)const;
	void prim(TypeOfVer startVer, TypeOfEdge noEdge)const;

	void dijkstra(TypeOfVer start, TypeOfEdge noEdge)const;
	void dijkstraPlus(TypeOfVer start, TypeOfEdge noEdge)const;
	void minusShortDistance(TypeOfVer start, TypeOfEdge noEdge)const;
	void dagShortDistance(TypeOfVer start, TypeOfEdge noEdge)const;


private:
	struct edgeNode//保存边的结点类
	{
		int end;
		TypeOfEdge weight;
		edgeNode *next;

		edgeNode(int e, TypeOfEdge w, edgeNode *n = NULL)
		{
			end = e;
			weight = w;
			next = n;
		}
	};

	struct verNode//保存顶点的结点类
	{
		TypeOfVer ver;
		edgeNode *head;

		verNode(edgeNode *h = nullptr) { head = h; }

	};

	struct EulerNode//保存欧拉回路的结点类
	{
		int NodeNum;
		EulerNode *next;
		EulerNode(int ver) { NodeNum = ver;next = nullptr; }
	};

	struct edge
	{
		int beg, end;
		TypeOfEdge w;
		bool operator<(const edge &rp)const { return w < rp.w; }
	};

	verNode *verList;
	void dfs(int start, bool p[]) const;
	EulerNode *EulerCircuit(int start, EulerNode *&end);
	verNode *clone()const;

	void findSeqNo(int start, int visited[], int &seqNo)const;
	void finddfs(int start, verNode *tmpV, int visited[])const;
	void find(int start, int m, int &top, bool visited[], int st[])const;
	bool checkRoute(int start, int end, bool visited[])const;
	bool isDAG(int start, bool visited[])const;
	void printPath(int start, int end, int prev[])const;
};

template<typename TypeOfVer, typename TypeOfEdge>
adjListGraph<TypeOfVer, TypeOfEdge>::adjListGraph(int vSize, const TypeOfVer d[])
{
	graph<TypeOfEdge>::Vers = vSize;
	graph<TypeOfEdge>::Edges = 0;
	verList = new verNode[vSize];
	for (int i = 0;i < graph<TypeOfEdge>::Vers;++i)
		verList[i].ver = d[i];
}

template<typename TypeOfVer, typename TypeOfEdge>
adjListGraph<TypeOfVer, TypeOfEdge>::~adjListGraph()
{
	int i;
	edgeNode *p;
	for (i = 0;i < graph<TypeOfEdge>::Vers;++i)
	{
		while ((p = verList[i].head) != nullptr)//释放第i个结点的单链表
		{
			verList[i].head = p->next;
			delete p;
		}
	}
	delete[]verList;
}

template<typename TypeOfVer,typename TypeOfEdge>
bool adjListGraph<TypeOfVer, TypeOfEdge>::insert(int u, int v, TypeOfEdge w)
{
	verList[u].head = new edgeNode(v, w, verList[u].head);
	++graph<TypeOfEdge>::Edges;
	return true;
}
template<typename TypeOfVer, typename TypeOfEdge>
bool adjListGraph<TypeOfVer, TypeOfEdge>::remove(int u, int v)
{
	edgeNode *p = verList[u].head, *q;
	if (p == nullptr)
		return false;
	if (p->end == v)
	{
		verList[u].head = p->next;
		delete p;
		--graph<TypeOfEdge>::Edges;
		return true;
	}
	while (p->next != nullptr&&p->next->end != v)
		p = p->next;
	if (p->next == nullptr)
		return false;
	q = q->next;p->next = q->next;delete q;
	--graph<TypeOfEdge>::Edges;
	return true;
}

template<typename TypeOfVer, typename TypeOfEdge>
bool adjListGraph<TypeOfVer, TypeOfEdge>::exist(int u, int v)const
{
	edgeNode *p = verList[u].head;
	while (p != nullptr&&p->end != v)
		p = p->next;
	if (p == nullptr)
		return false;
	else
		return true;
}

template<typename TypeOfVer, typename TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::dfs()const
{
	int i;
	bool *visited = new bool[graph<TypeOfEdge>::Vers];
	for (i = 0;i < graph<TypeOfEdge>::Vers;++i)
		visited[i] = false;
	std::cout << "当前图的深度优先遍历序列为：" << std::endl;

	for (i = 0;i < graph<TypeOfEdge>::Vers;++i)
	{
		if (visited[i] == true)continue;
		dfs(i, visited);
		std::cout << std::endl;
	}
}

template<typename TypeOfVer, typename TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::bfs()const
{
	bool *visited = new bool[graph<TypeOfEdge>::Vers];
	int currentNode,i;
	std::queue<int>q;
	edgeNode *p;

	for (i = 0;i < graph<TypeOfEdge>::Vers;++i)
		visited[i] = false;
	std::cout << "当前图的广度优先遍历序列为：" << std::endl;
	for (i = 0;i < graph<TypeOfEdge>::Vers;++i)
	{
		if (visited[i] == true)
			continue;
		q.push(i);
		while (!q.empty())
		{
			currentNode = q.front();
			q.pop();
			if (visited[currentNode] == true)
				continue;
			std::cout << verList[currentNode].ver << '\t';
			visited[currentNode] = true;
			p = verList[currentNode].head;
			while (p != nullptr)
			{
				if (visited[p->end] == false)q.push(p->end);
				p = p->next;
			}
		}
		std::cout << std::endl;
	}
}


template<typename TypeOfVer, typename TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::EulerCircuit(TypeOfVer start)
{
	EulerNode*beg, *end, *p, *q, *tb, *te;
	int numOfDegree,i;
	edgeNode *r;
	verNode *tmp;

	if (graph<TypeOfEdge>::Edges == 0)
	{
		std::cout << "不存在欧拉回路" << std::endl;
		return;
	}
	for (i = 0;i < graph<TypeOfEdge>::Vers;++i)
	{
		numOfDegree = 0;
		r = verList[i].head;
		while (r != 0)
		{
			++numOfDegree;
			r = r->next;
		}
		if (numOfDegree == 0 || numOfDegree % 2)
		{
			std::cout << "不存在欧拉回路" << std::endl;
			return;
		}
		for (i = 0;i < graph<TypeOfEdge>::Vers;++i)
		{
			if (verList[i].ver == start)break;
		}
		if (i == graph<TypeOfEdge>::Vers)
		{
			std::cout << "起始节点不存在" << std::endl;return;
		}
		tmp = clone();//创建一份邻接表的复制
		//寻找从i出发的路径，路径的起点和终点地址分别是beg和end
		beg = EulerCircuit(i, end);
		while (true)
		{
			p = beg;
			while (p->next != nullptr)//检查是否有边尚未被访问
				if (verList[p->next->NodeNum].head != nullptr)break;
				else p = p->next;
			if (p->next == nullptr)break;//所有的边都已被访问
			q = p->next;
			tb = EulerCircuit(q->NodeNum, te);//从此结点开始深度优先搜索
			te->next = q->next;
			p->next = tb;
			delete q;
		}
		//恢复原图
		delete[]verList;
		verList = tmp;

		//显示得到的欧拉回路
		std::cout << "欧拉回路是：" << std::endl;
		while (beg != nullptr)
		{
			std::cout << verList[beg->NodeNum].ver << '\t';
			p = beg;beg = beg->next;
			delete p;
		}
		std::cout << std::endl;
	}
}


template<typename TypeOfVer, typename TypeOfEdge>
typename adjListGraph<TypeOfVer, TypeOfEdge>::verNode * adjListGraph<TypeOfVer, TypeOfEdge>::clone()const
{
	verNode *tmp = new verNode[graph<TypeOfEdge>::Vers];
	edgeNode *p;

	for (int i = 0;i < graph<TypeOfEdge>::Vers;++i)
	{
		tmp[i].ver = verList[i].ver;
		p = verList[i].head;
		while (p != nullptr)
		{
			tmp[i].head = new edgeNode(p->end, p->weight, tmp[i].head);
			p = p->next;
		}
	}
	return tmp;
}

template<typename TypeOfVer, typename TypeOfEdge>
typename adjListGraph<TypeOfVer, TypeOfEdge>::EulerNode *adjListGraph<TypeOfVer, TypeOfEdge>::EulerCircuit(int start, EulerNode *&end)
{
	EulerNode *beg;
	int nextNode;

	beg = end = new EulerNode(start);
	while (verList[start].head != nullptr)
	{
		nextNode = verList[start].head->end;
		remove(start, nextNode);
		remove(nextNode, start);
		start = nextNode;
		end->next = new EulerNode(start);
		end = end->next;
	}
	return beg;
}

template<typename TypeOfVer, typename TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::queueTopSort()const
{
	std::queue<int>q;
	edgeNode *p;
	int current,i;
	int *inDegree = new int[graph<TypeOfEdge>::Vers];

	for (i = 0;i < graph<TypeOfEdge>::Vers;++i)
		inDegree[i] = 0;
	for (i = 0;i < graph<TypeOfEdge>::Vers;++i)
	{
		for (p = verList[i].head;p != nullptr;p = p->next)
			++inDegree[p->end];
	}
	for (i = 0;i < graph<TypeOfEdge>::Vers;++i)
	{
		if (inDegree[i] == 0)
			q.push(i);
	}
	std::cout << "拓扑排序为：" << std::endl;
	while (!q.empty())
	{
		current = q.front();
		q.pop();
		std::cout << verList[current].ver << '\t';
		for (p = verList[current].head;p != nullptr;p = p->next)
			if (--inDegree[p->end] == 0)
				q.push(p->end);
	}
	std::cout << std::endl;
}

template<typename TypeOfVer, typename TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::findStrong()const
{
	int *visited = new int[graph<TypeOfEdge>::Vers];
	int seqNo = 0, noOfStrong;
	int i;

	for (i = 0;i < graph<TypeOfEdge>::Vers;++i)
		visited[i] = -1;
	for (i = 0;i < graph<TypeOfEdge>::Vers;++i)//给结点编号
	{
		if (visited[i] >= 0)continue;
		findSeqNo(i, visited, seqNo);
	}
	//生成Gr
	verNode *tmpV = new verNode[graph<TypeOfEdge>::Vers];
	edgeNode *oldp, *newp;
	for (i = 0;i < graph<TypeOfEdge>::Vers;++i)
	{
		oldp = verList[i].head;
		while (oldp != nullptr)
		{
			tmpV[oldp->end].head = new edgeNode(i, oldp->weight, tmpV[oldp->end].head);
			oldp = oldp->next;
		}
	}

	//按序号从大到小的次序遍历Gr，输出所有强连通分量
	noOfStrong = 0;
	for (seqNo = graph<TypeOfEdge>::Vers - 1;seqNo >= 0;--seqNo)
	{
		for (i = 0;i < graph<TypeOfEdge>::Vers;++i)
			if (visited[i] == seqNo)break;
		if (i == graph<TypeOfEdge>::Vers)
			continue;
		++noOfStrong;
		std::cout << std::endl << "第" << noOfStrong << "个强连通分量:";
		finddfs(i, tmpV, visited);
	}

	for (i = 0;i < graph<TypeOfEdge>::Vers;++i)
	{
		oldp = tmpV[i].head;
		while (oldp != nullptr)
		{
			newp = oldp;
			oldp = oldp->next;
			delete newp;
		}
	}
	delete[]tmpV;
}

template <typename TypeOfVer, typename TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::finddfs(int start, verNode *tmpV, int visited[])const
{
	edgeNode *p = tmpV[start].head;

	std::cout << verList[start].ver << '\t';
	visited[start] = -1;
	while (p!=nullptr)
	{
		if (visited[p->end] != -1)
			finddfs(p->end, tmpV, visited);
		p = p->next;
	}
}
//找出所有强连通分量
template <typename TypeOfVer, typename TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::findSeqNo(int start, int visited[], int &seqNo)const
{
	edgeNode *p = verList[start].head;
	visited[start] = -2;
	while (p != nullptr)
	{
		if (visited[p->end] == -1)
			findSeqNo(p->end, visited, seqNo);
		p = p->next;
	}
	visited[start] = seqNo++;
}

//不采用队列实现拓扑排序
template <typename TypeOfVer, typename TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::topSort()const
{
	edgeNode *p;
	int current, i;
	int *inDegree = new int[graph<TypeOfEdge>::Vers];//保存每个节点当前的入度
	bool *visited = new bool[graph<TypeOfEdge>::Vers];//节点是否被访问过的标记

	for (i = 0;i < graph<TypeOfEdge>::Vers;++i)
	{
		inDegree[i] = 0;
		visited[i] = false;
	}
	for (i = 0;i < graph<TypeOfEdge>::Vers;++i)//计算节点入度
		for (p = verList[i].head;p != nullptr;p = p->next)
			++inDegree[p->end];

	std::cout << "拓扑排序为:" << std::endl;
	for (i = 0;i < graph<TypeOfEdge>::Vers;++i)//执行graph<TypeOfEdge>::Vers次输出
	{
		for (current = 0;current < graph<TypeOfEdge>::Vers;++current)//寻找可以输出的结点
			if (inDegree[current] == 0 && !visited[current])
				break;
		std::cout << verList[current].ver << '\t';
		visited[current] = true;
		for (p = verList[current].head;p != nullptr;p = p->next)
			--inDegree[p->end];
	}
	std::cout << std::endl;
}
//找出从指定结点出发、长度为M 的所有简单路径
template <typename TypeOfVer, typename TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::find(TypeOfVer start, int m)const
{
	bool *visited = new bool[graph<TypeOfEdge>::Vers];
	int *stack = new int[m + 1], top = 0;//存储路径信息
	int i;

	for (i = 0;i < graph<TypeOfEdge>::Vers;++i)//查找起点的编号
		visited[i] = false;
	for (i = 0;i < graph<TypeOfEdge>::Vers;++i)
		if (verList[i].ver == start)
			break;
	if (i == graph<TypeOfEdge>::Vers)
	{
		std::cout << "起点不存在" << std::endl;
		return;
	}

	find(i, m, top, visited, stack);
}

template<class TypeOfVer,class TypeOfEdge>//私有的find函数
void adjListGraph<TypeOfVer, TypeOfEdge>::find(int start, int m, int &top, bool visited[], int st[])const
{
	edgeNode * p = verList[start].head;

	visited[start] = true;
	st[top++] = start;
	if (top == m + 1)//路径长度等于m，递归终止
	{
		std::cout << std::endl;
		for (int i = 0;i < top;++i)//输出路径
			std::cout << verList[st[i]].ver << '\t';
		visited[start] = false;
		--top;
		return;
	}
	while (p != nullptr)//继续深度优先遍历
	{
		if (!visited[p->end])
			find(p->end, m, top, visited, st);
		p = p->next;
	}
	visited[start] = false;
	--top;
}
//检查图中任意两点之间是否有路径存在
template<class TypeOfVer, class TypeOfEdge>
bool adjListGraph<TypeOfVer, TypeOfEdge>::checkRoute(TypeOfVer start, TypeOfVer end)const
{
	bool *visited = new bool[graph<TypeOfEdge>::Vers];
	int startNo, endNo;

	for (int i = 0;i < graph<TypeOfEdge>::Vers; ++i)//数组visited初始化
		visited[i] = false;
	//检查起点和终点是否存在
	for (startNo = 0;startNo < graph<TypeOfEdge>::Vers;++startNo)
		if (verList[startNo].ver == start)
			break;
	if (startNo == graph<TypeOfEdge>::Vers)
	{
		std::cout << "起点不存在" << std::endl;
		return false;
	}

	for (endNo = 0;endNo < graph<TypeOfEdge>::Vers;++endNo)
		if (verList[endNo].ver == end)
			break;
	if (endNo == graph<TypeOfEdge>::Vers)
	{
		std::cout << "终点不存在" << std::endl;
		return false;
	}

	return checkRoute(startNo, endNo, visited);

}

template<typename TypeOfVer, typename TypeOfEdge>
bool adjListGraph<TypeOfVer, TypeOfEdge>::checkRoute(int start, int end, bool visited[])const//私有的checkRoute函数
{
	edgeNode *p = verList[start].head;
	bool flag;

	visited[start] = true;
	while (p != nullptr)
	{
		if (p->end == end)
			return true;//遇到终点
		if (!visited[p->end])//继续深度优先遍历
		{
			flag = checkRoute(p->end, end, visited);
			if (flag)
				return true;//本次遍历中遇到终点
		}
		p = p->next;
	}
	return false;
}
//增加一个DFS 函数，允许该函数接受一个指定搜索起始位置的参数
template<typename TypeOfVer, typename TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::dfs(TypeOfVer start)const
{
    int sNo, i ;
	for (sNo = 0;sNo < graph<TypeOfEdge>::Vers;++sNo)//检查起始节点是否存在
		if (verList[sNo].ver == start)
			break;
	if (sNo == graph<TypeOfEdge>::Vers)
	{
		std::cout << "起始节点不存在" << std::endl;
		return;
	}
	bool *visited = new bool[graph<TypeOfEdge>::Vers];
	for (i = 0;i < graph<TypeOfEdge>::Vers;++i)
		visited[i] = false;
	std::cout << "当前图的深度优先遍历序列为：" << std::endl;
	dfs(sNo, visited);
	std::cout << std::endl;
	for (i = 0;i < graph<TypeOfEdge>::Vers;++i)
	{
		if (visited[i] == true)
			continue;
		dfs(i, visited);
		std::cout << std::endl;
	}
}
template<typename TypeOfVer, typename TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::dfs(int start, bool visited[])const
{
	edgeNode *p = verList[start].head;
	std::cout << verList[start].ver << '\t';//访问结点
	visited[start] = true;

	while (p != nullptr)//对start的后继结点执行dfs
	{
		if (visited[p->end] == false)
			dfs(p->end, visited);
		p = p->next;
	}
}

//增加一个BFS 函数，允许该函数接受一个指定搜索起始位置的参数；
template<typename TypeOfVer, typename TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::bfs(TypeOfVer start)const
{
	int sNo, i, currentNode;
	bool *visited = new bool[graph<TypeOfEdge>::Vers];
	std::queue<int> q;
	edgeNode *p;
	int a;

	for (sNo = 0;sNo < graph<TypeOfEdge>::Vers;++sNo)//检查起始节点是否存在
		if (verList[sNo].ver == start)
			break;
	if (sNo == graph<TypeOfEdge>::Vers)
	{
		std::cout << "起始节点不存在" << std::endl;
		return;
	}

	for (int i = 0;i < graph<TypeOfEdge>::Vers;++i)
		visited[i] = false;
	std::cout << "当前图的广度优先遍历序列为：" << std::endl;
	for (i = sNo;i < graph<TypeOfEdge>::Vers + sNo;++i)
	{
		a = i%graph<TypeOfEdge>::Vers;
		if (visited[i] == true)
			continue;
		q.push(a);
		while (!q.empty())
		{
			currentNode = q.front();
			q.pop();
			if (visited[currentNode] == true)continue;
			std::cout << verList[currentNode].ver << '\t';
			visited[currentNode] = true;
			p = verList[currentNode].head;
			while (p != nullptr)
			{
				if (visited[p->end] == false)q.push(p->end);
				p = p->next;
			}
		}
	}
	std::cout << std::endl;
}
//增加一个函数，检验一个有向图是否为有向无环图（DAG）
template<typename TypeOfVer, typename TypeOfEdge>
bool adjListGraph<TypeOfVer, TypeOfEdge>::isDAG()const//共有函数
{
	bool *visited = new bool[graph<TypeOfEdge>::Vers];
	bool flag;
	int i;

	for (i = 0;i < graph<TypeOfEdge>::Vers;++i)
	{
		flag = isDAG(i, visited);
		if (!flag)return false;
		visited[i] = false;//为下一次一笔画做准备
	}
	return true;
}

template<typename TypeOfVer, typename TypeOfEdge>
bool adjListGraph<TypeOfVer, TypeOfEdge>::isDAG(int start, bool visited[])const//私有函数
{
	edgeNode *p = verList[start].head;
	bool flag;

	visited[start] = true;
	while (p != nullptr)
	{
		if (visited[p->end])
			return false;
		else flag = isDAG(p->end, visited);
		if (!flag)return false;
		visited[p->end] = false;
		p = p->next;
	}
	return true;
}

template<typename TypeOfVer, typename TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::kruskal()const
{
	int edgesAccepted = 0, u, v, i;
	edgeNode *p;
	edge e;
	DisjointSet ds(graph<TypeOfEdge>::Vers);
	std::priority_queue<edge, std::vector<edge>, std::greater<edge> >pq;

	//生成优先级队列
	for (i = 0;i < graph<TypeOfEdge>::Vers;++i)
	{
		for (p = verList[i].head;p != nullptr;p = p->next)
			if (i < p->end)
			{
				e.beg = i;
				e.end = p->end;
				e.w = p->weight;
				pq.push(e);
			}
	}
	//开始归并
	while (edgesAccepted < graph<TypeOfEdge>::Vers - 1)
	{
		e = pq.top();pq.pop();
		u = ds.Find(e.beg);
		v = ds.Find(e.end);
		if (u != v)
		{
			edgesAccepted++;
			ds.Union(u, v);
			std::cout << '(' << verList[e.beg].ver << ',' << verList[e.end].ver << ")\t";
		}
	}
}

template<typename TypeOfVer, typename TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::prim(TypeOfEdge noEdge)const
{
	bool *flag = new bool[graph<TypeOfEdge>::Vers];
	TypeOfEdge *lowCost = new TypeOfEdge[graph<TypeOfEdge>::Vers];
	int *startNode = new int[graph<TypeOfEdge>::Vers];

	edgeNode *p;
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
		for (p = verList[start].head;p != nullptr;p = p->next)
			if (!flag[p->end] && lowCost[p->end]>p->weight)
			{
				lowCost[p->end] = p->weight;
				startNode[p->end] = start;
			}
		flag[start] = true;
		min = noEdge;
		for (j = 0;j < graph<TypeOfEdge>::Vers;++j)
			if (lowCost[j] < min)
			{
				min = lowCost[j];
				start = j;
			}
		std::cout << '(' << verList[startNode[start]].ver << ',' << verList[start].ver << '\t';
		lowCost[start] = noEdge;
	}
	delete[]flag;
	delete[]startNode;
	delete[]lowCost;
}

template<typename TypeOfVer, typename TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::prim(TypeOfVer startVer, TypeOfEdge noEdge)const
{
	bool *flag = new bool[graph<TypeOfEdge>::Vers];
	TypeOfEdge *lowCost = new TypeOfEdge[graph<TypeOfEdge>::Vers];
	int *startNode = new int[graph<TypeOfEdge>::Vers];

	edgeNode *p;
	TypeOfEdge min;
	int start, i, j;

	for (start = 0;start < graph<TypeOfEdge>::Vers;++start)
		if (verList[start].ver == startVer)
			break;
	if (start == graph<TypeOfEdge>::Vers)
	{
		std::cout << "起始结点不存在" << std::endl;
		return;
	}
	for (i = 0;i < graph<TypeOfEdge>::Vers;++i)
	{
		flag[i] = false;
		lowCost[i] = noEdge;
	}

	for (i = 1;i < graph<TypeOfEdge>::Vers;++i)
	{
		for(p = verList[start].head;p != nullptr;p = p->next)
			if (!flag[p->end] && lowCost[p->end]>p->weight)
			{
				lowCost[p->end] = p->weight;
				startNode[p->end] = start;
			}
		flag[start] = true;
		min = noEdge;
		for (j = 0;j < graph<TypeOfEdge>::Vers;++j)
			if (lowCost[j] < min)
			{
				min = lowCost[j];
				start = j;
			}
		std::cout << '(' << verList[startNode[start]].ver << ',' << verList[start].ver << ")\t";
		lowCost[start] = noEdge;
	}
	delete[]flag;
	delete[]startNode;
	delete[]lowCost;
}

template<typename TypeOfVer, typename TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::kruskal(TypeOfVer startVer)const
{
	int edgesAccepted = 0, u, v, i;
	edgeNode *p;
	edge e;
	DisjointSet ds(graph<TypeOfEdge>::Vers);
	std::priority_queue<edge, std::vector<edge>, std::greater<edge> >pq;

	for (start = 0;start < graph<TypeOfEdge>::Vers;++start)
		if (verList[start].ver == startVer)
			break;
	if (start == graph<TypeOfEdge>::Vers)
	{
		std::cout << "起始结点不存在" << std::endl;
		return;
	}

	//生成优先级队列
	for (i = 0;i < graph<TypeOfEdge>::Vers;++i)
	{
		for (p = verList[i].head;p != nullptr;p = p->next)
			if (i < p->end)
			{
				e.beg = i;
				e.end = p->end;
				e.w = p->weight;
				pq.push(e);
			}
	}
	//开始归并
	while (edgesAccepted < graph<TypeOfEdge>::Vers - 1)
	{
		e = pq.front();pq.pop();
		u = ds.Find(e.beg);
		v = ds.Find(e.end);
		if (u != v)
		{
			edgesAccepted++;
			ds.Union(u, v);
			std::cout << '(' << verList[e.beg].ver << ',' << verList[e.end].ver << ")\t";
		}
	}
}

template<typename TypeOfVer, typename TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge> ::dijkstra(TypeOfVer start, TypeOfEdge noEdge)const
{
	TypeOfEdge *distance = new TypeOfEdge[graph<TypeOfEdge>::Vers];
	int *prev = new int[graph<TypeOfEdge>::Vers];
	bool *known = new bool[graph<TypeOfEdge>::Vers];

	int u, sNo, i, j;
	edgeNode *p;
	TypeOfEdge min;

	for (i = 0;i < graph<TypeOfEdge>::Vers;++i)
	{
		known[i] = false;
		distance[i] = noEdge;
	}
	for (sNo = 0;sNo < graph<TypeOfEdge>::Vers;++sNo)
		if (verList[sNo].ver == start)break;
	if (sNo = graph<TypeOfEdge>::Vers)
	{
		std::cout << "起始结点不存在" << std::endl;
		return;
	}
	distance[sNo] = 0;
	prev[sNo] = sNo;

	for (i = 1;i < graph<TypeOfEdge>::Vers;++i)
	{
		min = noEdge;
		for (j = 0;j < graph<TypeOfEdge>::Vers;++i)
			if (!known[j] && distance[j] < min)
			{
				min = distance[j];
				u = j;
			}
		known[u] = true;
		for (p = verList[u].head;p != nullptr;p = p->next)
			if (!known[p->end] && distance[p->end]>min + p->weight)
			{
				distance[p->end] = min + p->weight;
				prev[p->end] = u;
			}
	}
	for (i = 0;i < graph<TypeOfEdge>::Vers;++i)
	{
		std::cout << "从" << start << "到" << verList[i].ver << "的路径为：" << std::endl;
		printPath(sNo, i, prev);
		std::cout << "\t长度为：" << distance[i] << std::endl;
	}
}

template<typename TypeOfVer, typename TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge> ::printPath(int start, int end, int prev[])const
{
	if (start == end)
	{
		std::cout << verList[start].ver;
		return;
	}
	printPath(start, prev[end], prev);
	std::cout << "-" << verList[end].ver;
}

template<typename TypeOfVer, typename TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge> ::minusShortDistance(TypeOfVer start, TypeOfEdge noEdge)const
{
	TypeOfEdge *distance = new TypeOfEdge[graph<TypeOfEdge>::Vers];
	int *prev = new int[graph<TypeOfEdge>::Vers];
	int u, sNo, i;
	edgeNode *p;
	std::queue<int>q;

	for (sNo = 0;sNo < graph<TypeOfEdge>::Vers;++sNo)
		if (verList[sNo].ver == start)break;
	if (sNo == graph<TypeOfEdge>::Vers)
	{
		std::cout << "起始结点不存在" << std::endl;
		return;
	}

	for (i = 0;i < graph<TypeOfEdge>::Vers;++i)
		distance[i] = noEdge;
	distance[sNo] = 0;
	prev[sNo] = sNo;
	q.push(sNo);

	while (!q.empty())
	{
		u = q.front();
		q.pop();
		for (p = verList[u].head;p != nullptr;p = p->next)
			if (distance[p->end]>distance[u] + p->weight)
			{
				distance[p->end] > distance[u] + p->weight;
				prev[p->end] = u;
				q.push(p->end);
			}
	}
	for (i = 0;i < graph<TypeOfEdge>::Vers;++i)
	{
		std::cout << "从" << start << "到" << verList[i].ver << "的路径为：" << std::endl;
		printPath(sNo, i, prev);
		std::cout << "\t长度为：" << distance[i] << std::endl;
	}
}

template<typename TypeOfVer, typename TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge> ::dagShortDistance(TypeOfVer start, TypeOfEdge noEdge)const
{
	TypeOfEdge *distance = new TypeOfEdge[graph<TypeOfEdge>::Vers];
	int *prev = new int[graph<TypeOfEdge>::Vers];
	int *inDegree = new int[graph<TypeOfEdge>::Vers];
	int current, sNo, i;
	edgeNode *p;
	std::queue<int>q;
	for (sNo = 0;sNo < graph<TypeOfEdge>::Vers;++sNo)
		if (verList[sNo].ver == start)break;
	if (sNo == graph<TypeOfEdge>::Vers)
	{
		std::cout << "起始结点不存在" << std::endl;
		return;
	}
	//计算结点的入度并检查起始结点的入度是否为0
	for (i = 0;i < graph<TypeOfEdge>::Vers;++i)inDegree[i] = 0;
	for (i = 0;i < graph<TypeOfEdge>::Vers;++i)
		for (p = verList[i].head;p != nullptr;p = p->next)
			++inDegree[p->end];
	if (inDegree[sNo] != 0)
	{
		std::cout << "源点的入度不为0\n";
		return;
	}

	//初始化
	for (i = 0;i < graph<TypeOfEdge>::Vers;++i)
		distance[i] = noEdge;
	distance[sNo] = 0;
	prev[sNo] = sNo;
	q.push(sNo);

	while (!q.empty())//按拓扑序列选择结点并更新距离和路径信息
	{
		current = q.front();
		q.pop();
		for (p = verList[current].head;p != nullptr;p = p->next)
		{
			if (distance[p->end]>distance[current] + p->weight)
			{
				distance[p->end] = distance[current] + p->weight;
				prev[p->end] = current;
			}
			if (--inDegree[p->end] == 0)
				q.push(p->end);
		}
	}
	for (i = 0;i < graph<TypeOfEdge>::Vers;++i)
	{
		std::cout << "从" << start << "到" << verList[i].ver << "的路径为：" << std::endl;
		printPath(sNo, i, prev);
		std::cout << "\t长度为：" << distance[i] << std::endl;
	}
}

template<typename TypeOfVer, typename TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge> ::dijkstraPlus(TypeOfVer start, TypeOfEdge noEdge)const
{
	TypeOfEdge *distance = new TypeOfEdge[graph<TypeOfEdge>::Vers];
	int *prev = new int[graph<TypeOfEdge>::Vers];
	int *hop = new int[graph<TypeOfEdge>::Vers];//保存经过的结点数
	bool *known = new bool[graph<TypeOfEdge>::Vers];

	int u, sNo, i, j;
	edgeNode *p;
	TypeOfEdge min;

	for (i = 0;i < graph<TypeOfEdge>::Vers;++i)//初始化
	{
		known[i] = false;
		distance[i] = noEdge;
		hop[i] = 0;
	}
	for (sNo = 0;sNo < graph<TypeOfEdge>::Vers;++sNo)//寻找起始结点
		if (verList[sNo].ver == start)break;
	if (sNo == graph<TypeOfEdge>::Vers)
	{
		std::cout << "起始结点不存在" << std::endl;
		return;
	}

	distance[sNo] = 0;
	prev[sNo] = sNo;

	for (i = 1;i < graph<TypeOfEdge>::Vers;++i)
	{
		min = noEdge;
		for (j = 0;j < graph<TypeOfEdge>::Vers;++i)
			if (!known[j] && distance[j] < min)
			{
				min = distance[j];
				u = j;
			}
		known[u] = true;
		for (p = verList[u].head;p != nullptr;p = p->next)
			if (!known[p->end] && (distance[p->end]>min + p->weight || distance[p->end] == min + p->weight&&hop[p->end]>hop[u] + 1))
			{
				distance[p->end] = min + p->weight;
				hop[p->end] = hop[u] + 1;
				prev[p->end] = u;
			}
	}
	for (i = 0;i < graph<TypeOfEdge>::Vers;++i)
	{
		std::cout << "从" << start << "到" << verList[i].ver << "的路径为：" << std::endl;
		printPath(sNo, i, prev);
		std::cout << "\t长度为：" << distance[i] << std::endl;
	}

}
