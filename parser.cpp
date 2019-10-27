#include "parser.hpp"
#include "env.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

parser::parser(env& e) : en(e) {}

#define RED(ss, tp) \
int tp; \
ss>>a;

bool parser::parse(const char* filename)
{
	std::ifstream reader(filename);
	if(!reader){
		std::cerr<<"B³¹d otwarcia pliku"<<std::endl;
		return false;
	}
	
	for( std::string line; getline( reader, line ); )
	{
		if(line.at(0) == ';'){
			line.erase(line.begin());
			std::istringstream iss(line);

			std::string opt;
			iss>>opt;
			
			if(opt == "MaxNodes:" || opt == "MaxProcs:"){
				RED(iss,a);
				en.numCores = std::max(en.numCores, a);
				std::cout<<"Preparing "<<en.numCores<<" cores"<<std::endl;
			}
			if(opt == "MaxRecords:" || opt == "MaxJobs:"){
				RED(iss,a);
				en.numJobs = std::max(en.numJobs, a);
				std::cout<<"Expecting "<<en.numJobs<<" jobs"<<std::endl;
				if(en.numJobs > 10000){
					en.numJobs = 10000;
					std::cout<<"Warning, truncated job amount to 10000, more jobs will be ignored"<<std::endl;
				}
			}
			  
		}
		else{
			int jnum, ncores, tarr, texc, trash;
			std::istringstream iss(line);
			
			iss>>jnum>>tarr>>trash>>texc>>ncores;
			if(!en.tryAddJob(std::make_unique<task>(jnum, ncores, tarr, texc)))
				std::cout<<"Failed to add job (malformed entry), id: "<<jnum<<std::endl;
			
		}
	}
	std::cout<<"Parser is done."<<std::endl;
	reader.close();
	return true;
}