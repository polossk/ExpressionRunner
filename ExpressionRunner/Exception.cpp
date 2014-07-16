#include "Exception.h"


void Exception::ComUnqualifiedName()
{
	puts(">>>! ERROR");
	puts(">>>! There's at least one error in your expression.");
	puts(">>>! The NAME of variable is illegal.\n");
}

void Exception::ComUnqualifiedSymbol()
{
	puts(">>>! ERROR");
	puts(">>>! There's at least one error in your expression.");
	puts(">>>! One SYMBOL of expression is illegal.\n");
}

void Exception::RunMissingOperator()
{
	puts(">>>! ERROR");
	puts(">>>! There's at least one error in your expression.");
	puts(">>>! One OPERATOR is missing in your expression.\n");
}

void Exception::RunMissingNumber()
{
	puts(">>>! ERROR");
	puts(">>>! There's at least one error in your expression.");
	puts(">>>! One NUMBER is missing in your expression.\n");
}

void Exception::RunMathError()
{
	puts(">>>! WARNING");
	puts(">>>! Your must create a value like nan(Not a Number) or inf(infinity).");
	puts(">>>! I can deal with it, but I can't promise that you can do it well.\n");
}

void Exception::QryEmptyVariableSet()
{
	puts(">>>! ERROR");
	puts(">>>! There's at least one error in your expression.");
	puts(">>>! The data base of defined variable is empty.\n");
}

void Exception::QryVariableExist(string name)
{
	puts(">>>! ERROR");
	puts(">>>! There's at least one error in your expression.");
	printf(">>>! VARIABLE named [%s] is Existed in data base.\n\n", name.c_str());
}

void Exception::QryNoSuchVariable(string name)
{
	puts(">>>! ERROR");
	puts(">>>! There's at least one error in your expression.");
	printf(">>>! No such VARIABLE named [%s] in data base.\n\n", name.c_str());
}

void Exception::MainCommandError()
{
	puts(">>>! ERROR");
	puts(">>>! There's at least one error in your expression.");
	puts(">>>! Unknown Command.\n");
}

void Exception::MainSyntaxError()
{
	puts(">>>! ERROR");
	puts(">>>! There's at least one error in your expression.");
	puts(">>>! Command Syntax Error, try that after reading help.\n");
}