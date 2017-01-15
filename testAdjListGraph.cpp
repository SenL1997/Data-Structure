#include "adjListGraph.h"

using namespace std;

int main()
{
	bool a = 0;
    //�½�g1�����޻�ͼ�����ڲ����������ݣ�
	//a) ����һ���������ҳ�����ͼ������ǿͨ��������
	//b) ����һ������������һ������ͼ�Ƿ�Ϊ�����޻�ͼ��DAG����
	//c) ����һ�������������ö���ʵ���������򣬲������㷨��ʱ�临�Ӷȣ�
	//d) ����һ���������ҳ���ָ��������������ΪM �����м�·����
	//e) ����һ�����������ͼ�������������֮���Ƿ����·����
	//f) ����һ��DFS ����������ú�������һ��ָ��������ʼλ�õĲ�����
	//g) ����һ��BFS ����������ú�������һ��ָ��������ʼλ�õĲ�����
	//�Լ��ڽӱ���Ĭ�ϵ�insert(),remove(),exist();
	adjListGraph<char, int>g1(4, "ABCD");
	//����insert();
	g1.insert(0, 1, 1);
	g1.insert(1, 2, 1);
	g1.insert(2, 1, 1);
	g1.insert(2, 3, 1);
	g1.insert(3, 1, 1);

	g1.findStrong();//�ҳ�����ͼ������ǿͨ��������
	cout << endl << endl;
	a = g1.isDAG();//����һ������ͼ�Ƿ�Ϊ�����޻�ͼ��DAG����
	if (a == 1)
		cout << "����ͼ�������޻�ͼ��DAG��" << endl;
	else
		cout << "����ͼ���������޻�ͼ��DAG��" << endl;
	cout << endl;
	cout << "��C����������Ϊ1�����м�·����";
	g1.find('C', 1);//�ҳ���ָ��������������ΪM �����м�·����
	//���ͼ�������������֮���Ƿ����·����
	cout << endl << endl;
	if (g1.checkRoute('A', 'B') == 1)
		cout << "A��B֮�����·��" << endl;
	else
		cout << "A��B֮�䲻����·��" << endl;
	if (g1.checkRoute('B', 'A') == 1)
		cout << "B��A֮�����·��" << endl;
	else
		cout << "B��A֮�䲻����·��" << endl;
	if (g1.checkRoute('A', 'C') == 1)
		cout << "A��C֮�����·��" << endl;
	else
		cout << "A��C֮�䲻����·��" << endl;
	if (g1.checkRoute('C', 'A') == 1)
		cout << "C��A֮�����·��" << endl;
	else
		cout << "C��A֮�䲻����·��" << endl;
	if (g1.checkRoute('A', 'D') == 1)
		cout << "A��D֮�����·��" << endl;
	else
		cout << "A��D֮�䲻����·��" << endl;
	if (g1.checkRoute('D', 'A') == 1)
		cout << "D��A֮�����·��" << endl;
	else
		cout << "D��A֮�䲻����·��" << endl;
	if (g1.checkRoute('B', 'C') == 1)
		cout << "B��C֮�����·��" << endl;
	else
		cout << "B��C֮�䲻����·��" << endl;
	if (g1.checkRoute('C', 'B') == 1)
		cout << "C��B֮�����·��" << endl;
	else
		cout << "C��B֮�䲻����·��" << endl;
	if (g1.checkRoute('B', 'D') == 1)
		cout << "B��D֮�����·��" << endl;
	else
		cout << "B��D֮�䲻����·��" << endl;
	if (g1.checkRoute('D', 'B') == 1)
		cout << "D��B֮�����·��" << endl;
	else
		cout << "D��B֮�䲻����·��" << endl;
	if (g1.checkRoute('C', 'D') == 1)
		cout << "C��D֮�����·��" << endl;
	else
		cout << "C��D֮�䲻����·��" << endl;
	if (g1.checkRoute('D', 'C') == 1)
		cout << "D��C֮�����·��" << endl;
	else
		cout << "D��C֮�䲻����·��" << endl;
	cout << endl << endl;

	cout << "��B��ʼ��";
	g1.dfs('B');//DFS ����������ú�������һ��ָ��������ʼλ�õĲ�����
	cout << "��C��ʼ��";
	g1.bfs('C');//BFS ����������ú�������һ��ָ��������ʼλ�õĲ�����

    //g2���ڲ�����������;
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
	cout << "g2�����ö���ʵ����������:" << endl;
	g2.topSort();//�����ö���ʵ����������;
	cout << "g2���ö���ʵ����������:" << endl;
	g2.queueTopSort();//���ö���ʵ����������;

	//����Prim��Kruskal
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
