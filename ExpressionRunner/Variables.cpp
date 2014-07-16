#include "Variables.h"
#include "Exception.h"

Variables::Variables()
{ 
	vars.clear();
	add("EXP", exp(1.0));
	add("PI", acos(-1.0));
	add("nan", nan(""));
	add("inf", numeric_limits<double>::infinity());
}


Variables::~Variables()
{
}

bool Variables::testString(string src, string flag)
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

bool Variables::CMDcls(string cmd)
{
	Exception error;
	transform(cmd.begin(), cmd.end(), cmd.begin(), ::tolower);
	if (cmd != "cls")
	{
		error.MainSyntaxError();
		return false;
	}
	else
	{
		vars.clear();
		add("EXP", exp(1.0));
		add("PI", acos(-1.0));
		add("nan", nan(""));
		add("inf", numeric_limits<double>::infinity());
	}
	return true;
}

bool Variables::CMDls(string cmd)
{
	Exception error;
	transform(cmd.begin(), cmd.end(), cmd.begin(), ::tolower);
	if (cmd != "ls")
	{
		error.MainSyntaxError();
		return false;
	}
	else
	{
		if (vars.empty())
		{
			error.QryEmptyVariableSet();
			return false;
		}
		else
		{
			map<string, double>::iterator it;
			for (it = vars.begin(); it != vars.end(); it++)
				cout << it->first << " = " << it->second << endl;
		}
	}
	return true;
}

bool Variables::CMDcat(string cmd)
{
	Exception error; string tmp = cmd;
	transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);
	if (!testString(tmp, "cat"))
	{
		error.MainSyntaxError();
		return false;
	}
	else
	{
		tmp.erase(0, 4); cmd.erase(0, 4);
		while (tmp[0] == ' ' || tmp[0] == '\t') tmp.erase(0, 1), cmd.erase(0, 1);
		if (cmd.empty())
		{
			error.MainSyntaxError();
			return false;
		}
		else
		{
			stringstream buf; buf << cmd;
			string name; buf >> name;
			cmd.erase(0, name.size());
			if (!cmd.empty())
			while (cmd[0] == ' ' || cmd[0] == '\t') cmd.erase(0, 1);
			if (!cmd.empty())
			{
				error.MainSyntaxError();
				return false;
			}
			else if (vars.empty())
			{
				error.QryEmptyVariableSet();
				return false;
			}
			else
			{
				map<string, double>::iterator it = vars.find(name);
				if (it != vars.end())
					cout << it->first << " = " << it->second << endl;
				else
				{
					error.QryNoSuchVariable(name);
					return false;
				}
			}
		}
	}
	return true;
}

bool Variables::CMDcp(string cmd)
{
	Exception error; string tmp = cmd;
	transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);
	if (!testString(tmp, "cp"))
	{
		error.MainSyntaxError();
		return false;
	}
	else
	{
		tmp.erase(0, 3); cmd.erase(0, 3);
		while (tmp[0] == ' ' || tmp[0] == '\t') tmp.erase(0, 1), cmd.erase(0, 1);
		if (cmd.empty())
		{
			error.MainSyntaxError();
			return false;
		}
		else
		{
			stringstream buf1; buf1 << cmd;
			string name1; buf1 >> name1;
			cmd.erase(0, name1.size());
			if (cmd.empty())
			{
				error.MainSyntaxError();
				return false;
			}
			while (cmd[0] == ' ' || cmd[0] == '\t') cmd.erase(0, 1);
			if (cmd.empty())
			{
				error.MainSyntaxError();
				return false;
			}
			stringstream buf2; buf2 << cmd;
			string name2; buf2 >> name2;
			cmd.erase(0, name2.size());
			if (!cmd.empty())
				while (cmd[0] == ' ' || cmd[0] == '\t') cmd.erase(0, 1);
			if (!cmd.empty())
			{
				error.MainSyntaxError();
				return false;
			}
			else if (vars.empty())
			{
				error.QryEmptyVariableSet();
				return false;
			}
			else
			{
				map<string, double>::iterator it = vars.find(name1);
				if (it != vars.end())
				{
					map<string, double>::iterator it2 = vars.find(name2);
					if (it2 == vars.end())
						vars.insert(make_pair(name2, it->second));
					else
					{
						error.QryVariableExist(name2);
						return false;
					}
				}
				else
				{
					error.QryNoSuchVariable(name1);
					return false;
				}
			}
		}
	}
	return true;
}

bool Variables::CMDrm(string cmd)
{
	Exception error; string tmp = cmd;
	transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);
	if (!testString(tmp, "rm"))
	{
		error.MainSyntaxError();
		return false;
	}
	else
	{
		tmp.erase(0, 3); cmd.erase(0, 3);
		while (tmp[0] == ' ' || tmp[0] == '\t') tmp.erase(0, 1), cmd.erase(0, 1);
		if (cmd.empty())
		{
			error.MainSyntaxError();
			return false;
		}
		else
		{
			stringstream buf; buf << cmd;
			string name; buf >> name;
			cmd.erase(0, name.size());
			if (!cmd.empty())
			while (cmd[0] == ' ' || cmd[0] == '\t') cmd.erase(0, 1);
			if (!cmd.empty())
			{
				error.MainSyntaxError();
				return false;
			}
			else if (vars.empty())
			{
				error.QryEmptyVariableSet();
				return false;
			}
			else
			{
				map<string, double>::iterator it = vars.find(name);
				if (it != vars.end())
					vars.erase(name);
				else
				{
					error.QryNoSuchVariable(name);
					return false;
				}
			}
		}
	}
	return true;
}

bool Variables::CMDmv(string cmd)
{
	Exception error; string tmp = cmd;
	transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);
	if (!testString(tmp, "mv"))
	{
		error.MainSyntaxError();
		return false;
	}
	else
	{
		tmp.erase(0, 3); cmd.erase(0, 3);
		while (tmp[0] == ' ' || tmp[0] == '\t') tmp.erase(0, 1), cmd.erase(0, 1);
		if (cmd.empty())
		{
			error.MainSyntaxError();
			return false;
		}
		else
		{
			stringstream buf1; buf1 << cmd;
			string name1; buf1 >> name1;
			cmd.erase(0, name1.size());
			if (cmd.empty())
			{
				error.MainSyntaxError();
				return false;
			}
			while (cmd[0] == ' ' || cmd[0] == '\t') cmd.erase(0, 1);
			if (cmd.empty())
			{
				error.MainSyntaxError();
				return false;
			}
			stringstream buf2; buf2 << cmd;
			string name2; buf2 >> name2;
			cmd.erase(0, name2.size());
			if (!cmd.empty())
			while (cmd[0] == ' ' || cmd[0] == '\t') cmd.erase(0, 1);
			if (!cmd.empty())
			{
				error.MainSyntaxError();
				return false;
			}
			else if (vars.empty())
			{
				error.QryEmptyVariableSet();
				return false;
			}
			else
			{
				map<string, double>::iterator it = vars.find(name1);
				if (it != vars.end())
				{
					map<string, double>::iterator it2 = vars.find(name2);
					if (it2 == vars.end())
						vars.insert(make_pair(name2, it->second)),
						vars.erase(name1);
					else
					{
						error.QryVariableExist(name2);
						return false;
					}
				}
				else
				{
					error.QryNoSuchVariable(name1);
					return false;
				}
			}
		}
	}
	return true;
}

void Variables::add(string n, double f)
{
	if (vars.find(n) != vars.end()) vars.erase(n);
	vars.insert(make_pair(n, f));
}

map<string, double>::iterator Variables::query(string n)
{
	return vars.find(n);
}