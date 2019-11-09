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
		std::cerr<<"Error opening file."<<std::endl;
		return false;
	}
	
	for( std::string line; getline( reader, line ); )
	{
		if(line.size() == 0)continue;
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
				/*if(en.numJobs > 10000){
					en.numJobs = 10000;
					std::cout<<"Warning, truncated job amount to 10000, more jobs will be ignored"<<std::endl;
				}*/
			}
			  
		}
		else{
			int jnum, ncores, /*tarr, texc,*/ trash;
			time_task_t texc, tarr;
			std::istringstream iss(line);
			
			iss>>jnum>>tarr>>trash>>texc>>ncores;
			
			std::cout<<"Parsing: "<<jnum<<std::endl;
			
			switch(en.tryAddJob(std::make_unique<task>(jnum, ncores, tarr, texc)))
			{
				case 1:
					std::cout<<"Failed to add job (malformed entry), id: "<<jnum<<std::endl;
					break;
				case 2:
					std::cout<<"Failed to add job (job queue full), id: "<<jnum<<std::endl;
					break;
				case 3:
					std::cout<<"Failed to add job (job requres more cores than max declared), id: "<<jnum<<std::endl;
					break;
				case 4:
					std::cout<<"Failed to add job (job has zero or less exec time), id: "<<jnum<<std::endl;
					break;
				case 5:
					std::cout<<"Failed to add job (job requires zero or less cores), id: "<<jnum<<std::endl;
					break;
			}
			
		}
	}
	std::cout<<"Parser is done."<<std::endl;
	reader.close();
	return true;
}