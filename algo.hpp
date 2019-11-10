#ifndef _ALGO_HPP_
#define _ALGO_HPP_

#include "env.hpp"
#include <vector>

struct solution{

};

class algo{
	protected:
		env& en;
		
		bool verbose{false};
		
	public:
		//void tune(...);
		algo(env &);
		virtual solution generateSolution() = 0;
		
		inline bool getVerbose()const {return verbose;}

};

class algo1 : public algo{
	std::vector <time_task_t> coreFreedomTime;
	
	int calcFreeCores(int when) const;
	
	public:
		algo1(env & e, bool v) : algo1(e)
		{
			verbose = v;
		}
		algo1(env & e);
		
		virtual solution generateSolution();
};

#endif