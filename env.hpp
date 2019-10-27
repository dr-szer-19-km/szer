#ifndef _ENV_HPP_
#define _ENV_HPP_

#ifdef _GNUG_
#define always_inline inline __attribute__((always_inline))
#else
#define always_inline inline
#endif

#include <vector>
#include <memory>

struct task{
	int id;
	int numCores;
	int timeArrival;
	int timeExec;
	
	task() = default;
	task(int i, int nc, int ta, int te) :
		id(i), numCores(nc), timeArrival(ta), timeExec(te) {}
};

class env{
std::vector<std::unique_ptr<task> > tasks;

public:
	int numJobs{0};
	int numCores{0};
	
	bool tryAddJob(std::unique_ptr<task>);
	

};

#endif