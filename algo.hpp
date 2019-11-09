#ifndef _ALGO_HPP_
#define _ALGO_HPP_

#include "env.hpp"
#include <vector>

struct solution{

};

class algo{
	protected:
		env& en;
	public:
		//void tune(...);
		algo(env &);
		virtual solution generateSolution() = 0;

};

class algo1 : public algo{
	std::vector <time_task_t> coreFreedomTime;
	
	int calcFreeCores(int when) const;
	
	public:
		algo1(env &);
		virtual solution generateSolution();
};

#endif