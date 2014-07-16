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
class Interface
{
public:
	Interface();
	~Interface();
	void WaitForInputCommand();
	void TerminateInterface();
	bool isTerminated();

private:
	bool terminated;
};