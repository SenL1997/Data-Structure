#include "adjListGraph.h"

using namespace std;

int main()
{
	bool a = 0;

	//²âÊÔPrimºÍKruskal
	adjListGraph<char, int>g3(6, "ABCDEF");
//	g3.insert(1, 2, 6);
//	g3.insert(1, 4, 5);
//	g3.insert(1, 3, 1);
//	g3.insert(2, 3, 5);
//	g3.insert(2, 1, 6);
//	g3.insert(2, 5, 3);
//	g3.insert(3, 1, 1);
//	g3.insert(3, 2, 5);
//	g3.insert(3, 5, 6);
//	g3.insert(3, 6, 4);
//	g3.insert(3, 4, 5);
//	g3.insert(4, 1, 5);
//	g3.insert(4, 3, 5);
//	g3.insert(4, 6, 2);
//	g3.insert(5, 2, 3);
//	g3.insert(5, 3, 6);
//	g3.insert(5, 6, 6);
//	g3.insert(6, 5, 6);
//	g3.insert(6, 3, 4);
//	g3.insert(6, 4, 2);

//    g3.insert(0, 1, 6);
//	g3.insert(0, 3, 5);
//	g3.insert(0, 2, 1);
//	g3.insert(1, 2, 5);
//	g3.insert(1, 0, 6);
//	g3.insert(1, 4, 3);
//	g3.insert(2, 0, 1);
//	g3.insert(2, 1, 5);
//	g3.insert(2, 4, 6);
//	g3.insert(2, 5, 4);
//	g3.insert(2, 3, 5);
//	g3.insert(3, 0, 5);
//	g3.insert(3, 2, 5);
//	g3.insert(3, 5, 2);
//	g3.insert(4, 1, 3);
//	g3.insert(4, 2, 6);
//	g3.insert(4, 5, 6);
//	g3.insert(5, 4, 6);
//	g3.insert(5, 2, 4);
//	g3.insert(5, 3, 2);
    g3.insert(0, 1, 1);
	g3.insert(0, 3, 3);
	g3.insert(0, 5, 5);
	g3.insert(1, 3, 1);
	g3.insert(1, 2, 2);
	g3.insert(3, 5, 1);
	g3.insert(3, 4, 2);
	g3.insert(2, 4, 2);
	g3.insert(5, 2, 1);
	g3.insert(5, 4, 2);

	//g3.kruskal();
	//g3.prim(-255);

	g3.dijkstra('A',-1);
	g3.dijkstra('B', -225);
	g3.dijkstra('C', -225);
	g3.dijkstra('D', -225);
	g3.dijkstra('E', -225);

	return 0;
}
