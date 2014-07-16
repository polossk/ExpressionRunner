#include "Interface.h"


Interface::Interface()
{
	puts("Expression Runner [version 1.0.0.3]");
	puts("(c) 2014 All rights reserved");
	puts("\n");
	printf(">>> ");
}


Interface::~Interface()
{
}

bool Interface::isTerminated() { return terminated; }

void Interface::WaitForInputCommand() { printf(">>> "); }

void Interface::TerminateInterface() { terminated = 1; }