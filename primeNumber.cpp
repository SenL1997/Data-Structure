#include <iostream>
#include <math.h>

using namespace std;

bool IsPrime(unsigned n);

int main()
{
    int N,m;
    cout<<"Please enter an unsigned number N: ";
    cin >> N;
    if(IsPrime(N)==false)
    {
        cout << "It isn't a prime number!"<<endl;
    }
    else
    {
        cout << "It is a prime number!"<<endl;
    }
    return 0;
}

bool IsPrime(unsigned n)
{
    if (n<2)
    {
        return false; //小于2的数不是素数
    }
    else if (n==2)
    {
        return true; //2是素数
    }
    else if (n%2==0)
    {
        return false; //偶数不是素数
    }
    for(unsigned i=3;i<sqrt(n)+1;++i)
    {
        if (0 == n % i)// 和比它的一半小数相除，若都除不尽，证明是素数
        {
            return false;// 若除尽，是合数
        }
    }
    return true; // 都没除尽，素数
}
