#include "adjMatrixGraph.h"

using namespace std;

int main()
{
	adjMatrixGraph<char, int>g1(4, "ABCD", -1);
	g1.insert(0, 1, 1);
	g1.insert(1, 2, 1);
	g1.insert(2, 1, 1);
	g1.insert(2, 3, 1);
	g1.insert(3, 1, 1);

    cout<<"g1:"<<endl;
	g1.bfs();
	g1.dfs();

	adjMatrixGraph<char, int>g2(6, "012345", -1);
	g2.insert(0, 1, 1);
    //g2.insert(0, 2, 1);
	g2.insert(1, 2, 1);
	g2.insert(1, 3, 1);
	//g2.insert(1, 4, 1);
	g2.insert(2, 0, 1);
	g2.insert(2, 4, 1);
	//g2.insert(2, 3, 1);
	//g2.insert(3, 1, 1);
	g2.insert(3, 2, 1);
	//g2.insert(3, 4, 1);
	g2.insert(3, 5, 1);
    g2.insert(4, 1, 1);
    //g2.insert(4, 2, 1);
    g2.insert(4, 3, 1);
    //g2.insert(4, 5, 1);
    g2.insert(5, 4, 1);
    //g2.insert(5, 3, 1);

    cout<<endl;
    cout<<"g2:"<<endl;
    g2.EulerCircuit('0');
    g2.EulerCircuit('1');
    g2.EulerCircuit('2');
    g2.EulerCircuit('3');
    g2.EulerCircuit('4');
    g2.EulerCircuit('5');

	adjMatrixGraph<char, int>g3(5, "01234", -1);
	g3.insert(0, 1, 1);
	//g3.insert(1, 0, 1);
	g3.insert(1, 2, 1);
	//g3.insert(2, 1, 1);
	g3.insert(2, 3, 1);
	//g3.insert(0, 2, 1);
	g3.insert(3, 4, 1);
	g3.insert(4, 0, 1);


	g3.EulerCircuit('1');
	g3.EulerCircuit('2');

	//g5用于测试拓扑排序,与adjListGraph类中g2相同;
	adjMatrixGraph<char, int>g5(10, "ABCDEFGHIJ",-1);
	g5.insert(0, 1, 1);
	g5.insert(0, 3, 1);
	g5.insert(1, 2, 1);
	g5.insert(1, 5, 1);
	g5.insert(2, 3, 1);
	g5.insert(3, 4, 1);
	g5.insert(2, 4, 1);
	g5.insert(5, 2, 1);
	g5.insert(6, 5, 1);
	g5.insert(6, 7, 1);
	g5.insert(7, 5, 1);
	g5.insert(7, 9, 1);
	g5.insert(9, 8, 1);
	cout << endl;
	g5.dfsTopSort();

	system("Pause");
	return 0;
}
