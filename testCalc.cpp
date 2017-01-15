#include "calc.h"
using namespace std;

int main()
{
    calc exp1("3 * ((1 + 1)^2)^3 / (4 - 2) - 10");
    cout << "3 * ((1 + 1)^2)^3 / (4 - 2) - 10 = " << exp1.result()<<endl;

    calc exp2("3 * (1 + 1)^(2^3) / (4 - 2) - 10");
    cout << "3 * (1 + 1)^(2^3) / (4 - 2) - 10 = " << exp2.result()<<endl;

    calc exp3("3 * 6 / 9 + 5");
    cout << "3 * 6 / 9 + 5 = " << exp3.result()<<endl;

    calc exp4("6 / 3 * 4 + 1");
    cout << "6 / 3 * 4 + 1 = " << exp4.result()<<endl;

    return 0;
}
