#include "algo.hpp"
#include "env.hpp"
#include <algorithm>
#include <fstream>
#include <set>
#include <cstdlib>

algo::algo(env& e) : en(e){}
algo1::algo1(env& e) : algo(e){
	coreFreedomTime.resize(e.numCores);
	std::fill(coreFreedomTime.begin(), coreFreedomTime.end(), 0);
}

int algo1::calcFreeCores(int when)const
{
	int ret = 0;
	for(const auto & i : coreFreedomTime)
	{
		if(i <= when)ret++;
	}
	return ret;
}
#include<iostream>
solution algo1::generateSolution()
{

	auto & jobList = en.getTaskList();
	
	std::ofstream out("output.txt");
	
	std::cout<<"Sorting for greedy...\n";
	std::sort(jobList.begin(), jobList.end(), [](const std::unique_ptr<task>& t1, const std::unique_ptr<task>& t2) -> bool { 
			return ((t1->timeArrival ^ t2->timeArrival) ? t1->timeArrival < t2->timeArrival : t1->numCores < t2-> numCores); //bitowe mogą być szybsze
	});
	std::cout<<"Sorting done.\n"<<std::endl;
	
	//if(getVerbose())en.listJobsByTimeExec();
	
	while(jobList.size() != 0)
	{
		auto &i = jobList.front();
		
		std::set<time_task_t> timez;
		for( const auto &j : coreFreedomTime) //różne możliwe czasy zwolnień procesorów
		{
			if(j >= i->timeArrival)timez.insert(j); //nie rozpatrujemy czasu przed przybyciem zadania
			else timez.insert(i->timeArrival);
		}
		
		while(timez.size() != 0){ //czy w danym czasie jest dość wolnych proców. można to ulepszyć
			auto act = timez.begin();
			
			if(calcFreeCores(*act) >= i->numCores) //jest
			{
				out<<i->id<<" "<<*act<<" "<<(i->timeExec + *act)<<" ";
			
				int req = i->numCores;
				for(int j = 0; j < coreFreedomTime.size(); j++) //nowe czasy zakończenia dla proców
				{
					if(coreFreedomTime[j] <= *act){
						req--;
						coreFreedomTime[j] = *act + i->timeExec;
						out<<j<<" ";
					}
					if(!req)break;
				}
				out<<"\n";
				break;
			}
			
			timez.erase(timez.begin()); //nie ma
		}
					{
						//std::cerr<<i->id<<"#";
						//for(const auto &z : timez)std::cerr<<z<<",";
						//std::cerr<<"\n";
					}
		if(timez.size() == 0) //nie udało się uszeregować.
		{
			std::cerr<<"Algo error! (Prosimy Pana dr. Drozdowskiego o łagodny wymiar kary.)"<<std::endl; //zawsze powinno się udać przy obecnej konstrukcji.
			for(const auto &z : timez)std::cerr<<z<<",";
			abort();
		}
		
		jobList.erase(jobList.begin());
					{
						//std::cerr<<"!!\n";
					}
	}
	
	std::cout<<"Algo done"<<std::endl;
	out.close();
}