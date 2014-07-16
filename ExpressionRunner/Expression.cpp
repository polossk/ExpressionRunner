#include "Exception.h"
#include "Variables.h"
#include "Expression.h"
extern Variables Database;
Expression::Expression() { _init(); }
Expression::Expression(string s){ _init(); src = s; ans = 0; }

Expression::~Expression()
{
}

double Expression::_calculate(string str)
{
	while (!num.empty()) num.pop();
	while (!opr.empty()) opr.pop();

	Exception error;
	int i = 0; char last = 0;
	int sz = str.size();

	for (i = 0; i < sz; i++)
	{
		if (isalpha(str[i]))
		{
			string name; name += str[i];
			for (; i + 1 < sz && (isalpha(str[i + 1]) || isdigit(str[i + 1])); i++)
				name += str[i + 1];

			map<string, double>::iterator it = Database.query(name);
			if (it == Database.returnEndFlag())
			{
				error.QryNoSuchVariable(name);
				return nan("");
			}
			else num.push(it->second);
		}

		else if (isdigit(str[i]))
		{
			stringstream buf; buf << (str.c_str() + i);
			double f; buf >> f; num.push(f);
			for (; i + 1 < sz && isdigit(str[i + 1]); i++);
			if (i + 1 < sz && str[i + 1] == '.')
				for (i++; i + 1 < sz && isdigit(str[i + 1]); i++);
			if (i + 1 < sz && str[i + 1] == 'e')
				for (i++; i + 1 < sz && isdigit(str[i + 1]); i++);
			for (; i + 1 < sz && isdigit(str[i + 1]); i++);
		}

		else if (str[i] == '(') opr.push(str[i]);

		else if (str[i] == ')')
		{
			while (opr.top() != '(')
				_operation();
			opr.pop();
		}

		else if (str[i] == '-' && (last == 0 || last == '('))
		{
			num.push(0.0);
			opr.push('-');
		}

		else if (priv[str[i]] > 0)
		{
			while (opr.size() > 0 && priv[str[i]] >= priv[opr.top()])
				_operation();
			opr.push(str[i]);
		}

		else if (str[i] == ' ' || str[i] == '\t') continue;
		else
		{
			error.ComUnqualifiedSymbol();
			return nan("");
		}
		last = str[i];
	}
	while (opr.size() > 0)
	{
		if (opr.top() == '(' || opr.top() == ')')
		{
			error.RunMissingOperator();
			return nan("");
		}
		else if (opr.size() == 1 && num.size() < 2)
		{
			error.RunMissingNumber();
			return nan("");
		}
		_operation();
	}
	double ans = num.top();
	if (isnan(ans) || isinf(ans)) error.RunMathError();
	else Database.add("Ans", ans);
	return ans;
}