/******************************************************************************
#       COPYRIGHT NOTICE
#       Copyright (c) 2014 All rights reserved
#       ----Stay Hungry Stay Foolish----
#
#       @author       :Shen
#       @name         :Main
#       @file         :main.cpp
#       @date         :2014/6/29 20:05
******************************************************************************/

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


#include "Exception.h"

#include "Interface.h"
Interface Main;

#include "Variables.h"
Variables Database;

#include "Expression.h"
#include "Assignment.h"

string modifyString(string src);
bool checkStringHead(string src, string flag);
bool checkStringIsExpression(string src);
bool checkStringIsAssignment(string src);
bool receiver(string cmd);

int main()
{
	string input;
	while (getline(cin, input))
	{
		receiver(input);
		if (Main.isTerminated()) return 0;
		Main.WaitForInputCommand();
	}
	return 0;
}

string modifyString(string src)
{
	while (src[0] == ' ' || src[0] == '\t') src.erase(0, 1);
	reverse(src.begin(), src.end());
	while (src[0] == ' ' || src[0] == '\t') src.erase(0, 1);
	reverse(src.begin(), src.end());
	return src;
}

bool checkStringHead(string src, string flag)
{
	int szsrc = src.size(), szflg = flag.size();
	transform(src.begin(), src.end(), src.begin(), ::tolower);
	if (szsrc < szflg) return false;
	else
	{
		bool success = 1;
		for (int i = 0; i < szflg; i++)
			success = success && (src[i] == flag[i]);
		success = success
			&& ((szflg == szsrc) ? true : (src[szflg] == ' ' || src[szflg] == '\t'));
		return success;
	}
}

bool checkStringIsExpression(string src)
{
	if (isdigit(src[0]))
	{
		while (isdigit(src[0])) src.erase(0, 1);
		return !isalpha(src[0]);
	}
	else if (isalpha(src[0])) return true;
	else if (src[0] == '-' || src[0] == '(') return true;
	else return false;
}

bool checkStringIsAssignment(string src)
{
	if (src.find(":=") < src.size())
		return true;
	else return false;
}

bool receiver(string cmd)
{
	bool success = false;
	Exception error;
	cmd = modifyString(cmd);
	if (cmd == "") return false;
	//exit
	else if (checkStringHead(cmd, "exit"))
		Main.TerminateInterface();
	//cls
	else if (checkStringHead(cmd, "cls"))
		success = Database.CMDcls(cmd);
	//ls
	else if (checkStringHead(cmd, "ls"))
		success = Database.CMDls(cmd);
	//cat
	else if (checkStringHead(cmd, "cat"))
		success = Database.CMDcat(cmd);
	//cp
	else if (checkStringHead(cmd, "cp"))
		success = Database.CMDcp(cmd);
	//rm
	else if (checkStringHead(cmd, "rm"))
		success = Database.CMDrm(cmd);
	//mv
	else if (checkStringHead(cmd, "mv"))
		success = Database.CMDmv(cmd);
	//assignment
	else if (checkStringIsAssignment(cmd))
	{
		Assignment a(cmd); a.run();
	}
	//expression
	else if (checkStringIsExpression(cmd))
	{
		Expression s(cmd); s.run();
		s.print();
	}
	else error.MainCommandError();
	return success;
}
