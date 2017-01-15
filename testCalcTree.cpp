#include "calcTree.h"

using namespace std;

int main()
{
	calc exp0("2 * 3 +(1 * 2 * 3 + 6 * 6) * (2 + 3) / 5 + 2 / 2 ");
    cout << "2 * 3 +(1 * 2 * 3 + 6 * 6) * (2 + 3) / 5 + 2 / 2 = " << exp0.result()<< endl;
    calc exp1("8 * 7");
    cout <<"8 * 7 = "<< exp1.result()<<endl;
    calc exp2("1 * 2 * 3 + 6 * 6");
    cout << "1 * 2 * 3 + 6 * 6 = " << exp2.result()<<endl;
    calc exp3("(3 + 5) * 7 / (8 - 4)");
    cout << "(3 + 5) * 7 / (8 - 4) = " << exp3.result()<<endl;//测试以(开头的情况
    calc exp4("(3 + 5)");
    cout << "(3 + 5) = " << exp4.result()<<endl;
    calc exp5("(8 - 4)");
    cout << "(8 - 4) = " << exp5.result()<<endl;
    calc exp6("(8 / 4)");
    cout << "(8 / 4) = " << exp6.result()<<endl;
    calc exp7("2 ^ (4 ^ 1)");
    cout << "2 ^ (4 ^ 1) = " << exp7.result()<<endl;//注意结果不能超过int的最大值
    calc exp8("(2 ^ 4) ^ 2");
    cout << "(2 ^ 4) ^ 2 = " << exp8.result()<<endl;//此处不能写成"2 ^ 4 ^ 2"
    calc exp9("1 + (2 ^ 4) ^ 2 / 2 ");
    cout << "1 + (2 ^ 4) ^ 2 / 2 = " << exp9.result()<<endl;
    calc exp10("1 + (2 ^ 4) ^ 2 / 2 - 2 * 2 ^ 6");
    cout << "1 + (2 ^ 4) ^ 2 / 2 - 2 * 2 ^ 6 = " << exp10.result()<<endl;
    cout << "The check result of exp1 is "<<exp1.check()<<endl;
    cout << "The check result of exp10 is "<<exp10.check()<<endl;
    calc illegal1("2 /* 2 + 4");//验证：结点的度数要么是0，要么是2，此处错误未1
    cout << "The check result of illegal1 is "<<illegal1.check()<<endl;

    return 0;
}
