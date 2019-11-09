#include <iostream>
#include "parser.hpp"
#include "env.hpp"
#include "algo.hpp"

#ifndef __GNUG__
#warning "Ten program był testowany pod kompilatorem GNU GCC 7.x"
#endif

int main(int argc, char * argv[])
{
	env Master;
	parser Parser(Master);
	Parser.parse("Sandia-Ross-2001-1.1-cln.swf");
	
	//Master.listJobsByTimeExec();
	
	algo1 Greedy(Master);
	
	std::cout<<"Starting solution generation."<<std::endl;
	
	Greedy.generateSolution();
	
	return 0;
}
