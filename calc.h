#ifndef CALC_H_INCLUDED
#define CALC_H_INCLUDED

#include <iostream>
#include <stack>
#include <vector>
#include <string.h>
#include <stdlib.h>
#include <math.h>

using namespace std;

class calc
{
	char * expression;
	enum token {OPAREN, ADD, SUB, MULTI, DIV, EXP, CPAREN, VALUE, EOL};

	void BinaryOp(token op, stack<int>&dataStack);
	token getOp (int &value);

	public:
		calc(char *s)
		{
			expression = new char[strlen(s)+1];
			strcpy(expression, s);
		}
		~calc(){delete expression;}

		int result();
};

int calc::result()
{
	token lastOp, topOp;
	int result_value, currentValue;
	stack<token> opStack;
	stack<int> dataStack;
	char *str = expression;

	//cout << currentValue<<"CurrentValue";

	while(true)
	{
		lastOp = getOp(currentValue);
		if (lastOp == EOL) break;
		switch(lastOp)
		{
			case VALUE:
                    //cout<<currentValue<<endl;
                    dataStack.push(currentValue);
				    break;
			case CPAREN:
				    while(!opStack.empty()&&(topOp = opStack.top())!=OPAREN)
                    {
                        opStack.pop();
                        BinaryOp(topOp,dataStack);
                    }
                    if(topOp==OPAREN) opStack.pop();
				    if(topOp!=OPAREN) cerr<< "No left parenthesis!"<<endl;
				    break;
			case OPAREN:opStack.push(OPAREN);break;
			case EXP:opStack.push(EXP);break;
			case MULTI:case DIV:
				while(!opStack.empty()&&opStack.top()>=MULTI)
                {
                    BinaryOp(opStack.top(), dataStack);
                    opStack.pop();
                }
				opStack.push(lastOp);
				break;
			case ADD:case SUB:
				while(!opStack.empty()&&opStack.top()!=OPAREN)
                {
                    BinaryOp(opStack.top(),dataStack);
                    opStack.pop();
                }
				opStack.push(lastOp);
		}
	}



	while (!opStack.empty())
    {
        BinaryOp(opStack.top(),dataStack);
        opStack.pop();
    }
	if(dataStack.empty())
	{
		cout<<"No result!"<<endl;
		return 0;
	}
	result_value = dataStack.top();
	dataStack.pop();
	if(!dataStack.empty())
	{
		cout <<"There is no operator!"<<endl;
		return 0;
	}

	expression = str;
	return result_value;
}

void calc::BinaryOp(token op, stack<int>&dataStack)
{
	int num1, num2;
	if(dataStack.empty())
	{ cerr <<"There is no operand!\n";exit(1);}
	else
    {
        num2 = dataStack.top();
        dataStack.pop();
    }
	if(dataStack.empty())
	{ cerr <<"There is no operand!\n";exit(1);}
	else
    {
        num1 = dataStack.top();
        dataStack.pop();
    }

	switch(op)
	{
		case ADD:dataStack.push(num1+num2);break;
		case SUB:dataStack.push(num1-num2);break;
		case MULTI:dataStack.push(num1*num2);break;
		case DIV:dataStack.push(num1/num2);break;
		case EXP:dataStack.push(pow(num1,num2));
	}
}

calc::token calc::getOp(int &value)
{
	while (*expression)
	{
		while (*expression && *expression ==' ')
			++expression;
		if(*expression <='9' && *expression >='0')
		{
			value = 0;
			while(*expression >= '0' && *expression <= '9')
			{
				value = value*10+*expression - '0';
				++expression;
			}
			return VALUE;
		}

		switch(*expression)
		{
			case'(':++expression;return OPAREN;
			case')':++expression;return CPAREN;
			case'+':++expression;return ADD;
			case'-':++expression;return SUB;
			case'*':++expression;return MULTI;
			case'/':++expression;return DIV;
			case'^':++expression;return EXP;
		}
	}
	return EOL;
}

#endif // CALC_H_INCLUDED
