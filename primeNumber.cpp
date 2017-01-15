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
        return false; //С��2������������
    }
    else if (n==2)
    {
        return true; //2������
    }
    else if (n%2==0)
    {
        return false; //ż����������
    }
    for(unsigned i=3;i<sqrt(n)+1;++i)
    {
        if (0 == n % i)// �ͱ�����һ��С�������������������֤��������
        {
            return false;// ���������Ǻ���
        }
    }
    return true; // ��û����������
}
