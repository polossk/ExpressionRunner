#include "Exception.h"
#include "Variables.h"
#include "Expression.h"
#include "Assignment.h"
extern Variables Database;

Assignment::Assignment()
{
}


Assignment::~Assignment()
{
}

Assignment::Assignment(string src)
{
	int i = 0; name.clear(); exps.clear();
	brun = false;
	Exception error;
	if (isalpha(src[0]))
	{
		name += src[0];
		src.erase(0, 1);
		while (isalpha(src[0]) || isdigit(src[0]))
		{
			name += src[0];
			src.erase(0, 1);
		}
		while (src[0] == ' ' || src[0] == '\t') src.erase(0, 1);
		if (src[0] == ':' && src[1] == '=')
		{
			src.erase(0, 2);
			while (src[0] == ' ' || src[0] == '\t') src.erase(0, 1);
			exps = src; brun = true;
		}
		else error.ComUnqualifiedName();
	}
	else error.ComUnqualifiedName();
}

void Assignment::run()
{
	if (brun)
	{
		Expression v(exps);
		double f = v.run();
		Database.add(name, f);
	}
	else return;
}