#include <iostream>
#include <string>
#include "parser.hpp"
#include "env.hpp"
#include "algo.hpp"

#ifndef __GNUG__
#warning "Ten program był testowany pod kompilatorem GNU GCC 7.x"
#endif

int main(int argc, char * argv[])
{
	
	std::ios_base::sync_with_stdio(false);

	env Master;
	parser Parser(Master);
	
	std::string opts;
	for(int i = 0; i < argc; i++)
	{
		if(i)opts += std::string(" ") + argv[i];
	}
	std::cout<<opts<<"\n";
	
	if(!Parser.parseOpts(opts))
	{
		return 1;
	}
	if(!Parser.parse())
	{
		std::cerr<<"Parser error. Invalid arguments."<<std::endl;
		return 1;
	}
	
	if(Parser.getVerbose())Master.listJobsByTimeExec();
	
	algo1 Greedy(Master, Parser.getVerbose(), Parser.getOutputFileName());
	
	std::cout<<"Starting solution generation."<<std::endl;
	
	Greedy.generateSolution();
	
	return 0;
}
