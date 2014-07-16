#ifndef H_STD_INCLUDE
#define H_STD_INCLUDE
	#include <map>	
	#include <cmath>
	#include <stack>
	#include <limits>
	#include <cctype>
	#include <string>
	#include <cstdio>
	#include <sstream>
	#include <cstdlib>
	#include <cstring>
	#include <iostream>
	#include <algorithm>
	using namespace std;
#endif // !H_STD_INCLUDE
#pragma once
class Expression
{
public:
	Expression();
	~Expression();
	Expression(string s);
	double	run()		{ return ans = _calculate(src); }
	string	toString()
	{
		stringstream printer;
		printer << src << " = ";
		if (isnan(ans)) printer << "nan";
		else if (isinf(ans)) printer << "inf";
		else printer << ans;
		string tar = printer.str();
		return tar;
	}
	void	print()				{ printf("%s\n", toString().c_str()); }

private:
	stack<double>		num;
	stack<char>			opr;
	map<char, int>		priv;
	double				ans;
	string				src;

	void _init()
	{
		priv.clear();
		while (!num.empty()) num.pop();
		while (!opr.empty()) opr.pop();
		priv.insert(make_pair<char, int>('+', 3));
		priv.insert(make_pair<char, int>('-', 3));
		priv.insert(make_pair<char, int>('*', 2));
		priv.insert(make_pair<char, int>('/', 2));
		priv.insert(make_pair<char, int>('^', 1));
		priv.insert(make_pair<char, int>('(', 10));
	}

	inline double _calc(double a, double b, char op)
	{
		//printf("[%lf] [%c] [%lf]\n", a, op, b);
		if (op == '+') return a + b;
		if (op == '-') return a - b;
		if (op == '*') return a * b;
		if (op == '/') return a / double(b);
		if (op == '^') return exp(log(double(a)) * b);
		else return nan("");
	}

	inline void _operation()
	{
		double x = 0.0, y = 0.0;
		Exception error;
		if (opr.top() == '(' || opr.top() == ')')
		{
			error.RunMissingOperator();
			return;
		}
		if (!num.empty()) y = num.top(), num.pop();
		else
		{
			error.RunMissingOperator();
			return;
		}
		if (!num.empty()) x = num.top(), num.pop();
		else
		{
			error.RunMissingOperator();
			return;
		}
		char op = opr.top();
		opr.pop();
		num.push(_calc(x, y, op));
	}
	double _calculate(string str);
};

