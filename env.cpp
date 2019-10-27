#include "env.hpp"

#include <memory>

bool env::tryAddJob(std::unique_ptr<task> t)
{
	if(t->numCores <= 0 || t->timeArrival < 0 || t->timeExec <= 0 || t->id < 0)
		return false;
	
	tasks.push_back(std::move(t));
		
	return true;
}