#include "adjListGraph.h"

using namespace std;

int main()
{
	bool a = 0;
    //新建g1有向无环图，用于测试以下内容：
	//a) 增加一个函数，找出有向图的所有强通连分量；
	//b) 增加一个函数，检验一个有向图是否为有向无环图（DAG）；
	//c) 增加一个函数，不采用队列实现拓扑排序，并给出算法的时间复杂度；
	//d) 增加一个函数，找出从指定结点出发、长度为M 的所有简单路径；
	//e) 增加一个函数，检查图中任意两个结点之间是否存在路径；
	//f) 增加一个DFS 函数，允许该函数接受一个指定搜索起始位置的参数；
	//g) 增加一个BFS 函数，允许该函数接受一个指定搜索起始位置的参数；
	//以及邻接表中默认的insert(),remove(),exist();
	adjListGraph<char, int>g1(4, "ABCD");
	//测试insert();
	g1.insert(0, 1, 1);
	g1.insert(1, 2, 1);
	g1.insert(2, 1, 1);
	g1.insert(2, 3, 1);
	g1.insert(3, 1, 1);

	g1.findStrong();//找出有向图的所有强通连分量；
	cout << endl << endl;
	a = g1.isDAG();//检验一个有向图是否为有向无环图（DAG）；
	if (a == 1)
		cout << "有向图是有向无环图（DAG）" << endl;
	else
		cout << "有向图不是有向无环图（DAG）" << endl;
	cout << endl;
	cout << "从C出发，长度为1的所有简单路径：";
	g1.find('C', 1);//找出从指定结点出发、长度为M 的所有简单路径；
	//检查图中任意两个结点之间是否存在路径；
	cout << endl << endl;
	if (g1.checkRoute('A', 'B') == 1)
		cout << "A和B之间存在路径" << endl;
	else
		cout << "A和B之间不存在路径" << endl;
	if (g1.checkRoute('B', 'A') == 1)
		cout << "B和A之间存在路径" << endl;
	else
		cout << "B和A之间不存在路径" << endl;
	if (g1.checkRoute('A', 'C') == 1)
		cout << "A和C之间存在路径" << endl;
	else
		cout << "A和C之间不存在路径" << endl;
	if (g1.checkRoute('C', 'A') == 1)
		cout << "C和A之间存在路径" << endl;
	else
		cout << "C和A之间不存在路径" << endl;
	if (g1.checkRoute('A', 'D') == 1)
		cout << "A和D之间存在路径" << endl;
	else
		cout << "A和D之间不存在路径" << endl;
	if (g1.checkRoute('D', 'A') == 1)
		cout << "D和A之间存在路径" << endl;
	else
		cout << "D和A之间不存在路径" << endl;
	if (g1.checkRoute('B', 'C') == 1)
		cout << "B和C之间存在路径" << endl;
	else
		cout << "B和C之间不存在路径" << endl;
	if (g1.checkRoute('C', 'B') == 1)
		cout << "C和B之间存在路径" << endl;
	else
		cout << "C和B之间不存在路径" << endl;
	if (g1.checkRoute('B', 'D') == 1)
		cout << "B和D之间存在路径" << endl;
	else
		cout << "B和D之间不存在路径" << endl;
	if (g1.checkRoute('D', 'B') == 1)
		cout << "D和B之间存在路径" << endl;
	else
		cout << "D和B之间不存在路径" << endl;
	if (g1.checkRoute('C', 'D') == 1)
		cout << "C和D之间存在路径" << endl;
	else
		cout << "C和D之间不存在路径" << endl;
	if (g1.checkRoute('D', 'C') == 1)
		cout << "D和C之间存在路径" << endl;
	else
		cout << "D和C之间不存在路径" << endl;
	cout << endl << endl;

	cout << "从B开始，";
	g1.dfs('B');//DFS 函数，允许该函数接受一个指定搜索起始位置的参数；
	cout << "从C开始，";
	g1.bfs('C');//BFS 函数，允许该函数接受一个指定搜索起始位置的参数；

    //g2用于测试拓扑排序;
	adjListGraph<char, int>g2(10, "ABCDEFGHIJ");
	g2.insert(0, 1, 1);
	g2.insert(0, 3, 1);
	g2.insert(1, 2, 1);
	g2.insert(1, 5, 1);
	g2.insert(2, 3, 1);
	g2.insert(3, 4, 1);
	g2.insert(2, 4, 1);
	g2.insert(5, 2, 1);
	g2.insert(6, 5, 1);
	g2.insert(6, 7, 1);
	g2.insert(7, 5, 1);
	g2.insert(7, 9, 1);
	g2.insert(9, 8, 1);
	cout << endl;
	cout << "g2不采用队列实现拓扑排序:" << endl;
	g2.topSort();//不采用队列实现拓扑排序;
	cout << "g2采用队列实现拓扑排序:" << endl;
	g2.queueTopSort();//采用队列实现拓扑排序;

	//测试Prim和Kruskal
	adjListGraph<char, int>g3(6, "123456");
	g3.insert(1, 2, 6);
	g3.insert(1, 4, 5);
	g3.insert(1, 3, 1);
	g3.insert(2, 3, 5);
	g3.insert(2, 1, 6);
	g3.insert(2, 5, 3);
	g3.insert(3, 1, 1);
	g3.insert(3, 2, 5);
	g3.insert(3, 5, 6);
	g3.insert(3, 6, 4);
	g3.insert(3, 4, 5);
	g3.insert(4, 1, 5);
	g3.insert(4, 3, 5);
	g3.insert(4, 6, 2);
	g3.insert(5, 2, 3);
	g3.insert(5, 3, 6);
	g3.insert(5, 6, 6);
	g3.insert(6, 5, 6);
	g3.insert(6, 3, 4);
	g3.insert(6, 4, 2);


	return 0;
}
