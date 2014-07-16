#pragma once
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
class Exception{
public:
	Exception(){}
	~Exception(){}
	void RunMissingOperator();
	void RunMissingNumber();
	void RunMathError();
	void ComUnqualifiedName();
	void ComUnqualifiedSymbol();
	void QryEmptyVariableSet();
	void QryVariableExist(string name);
	void QryNoSuchVariable(string name);
	void MainCommandError();
	void MainSyntaxError();
};