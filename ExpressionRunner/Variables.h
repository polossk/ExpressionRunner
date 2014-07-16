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

class Variables
{
	typedef map<string, double>::iterator itor;
public:
	Variables();
	~Variables();
	bool CMDcls(string cmd);
	bool CMDls(string cmd);
	bool CMDcat(string cmd);
	bool CMDcp(string cmd);
	bool CMDmv(string cmd);
	bool CMDrm(string cmd);
	void add(string n, double f);
	itor query(string n);
	itor returnEndFlag(){ return vars.end(); }
private:
	bool testString(string src, string flag);
	map<string, double> vars;
};