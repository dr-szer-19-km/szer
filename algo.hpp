#ifndef _ALGO_HPP_
#define _ALGO_HPP_

#include "env.hpp"
#include <vector>
#include <string>

class algo{
	protected:
		env& en;
		
		bool verbose{false};
		std::string outp{"output.txt"};
		
	public:
		algo(env &);
		virtual void generateSolution() = 0;
		
		inline bool getVerbose()const {return verbose;}

};

class algo1 : public algo{
	std::vector <time_task_t> coreFreedomTime;
	
	int calcFreeCores(int when) const;
	
	public:
		algo1(env & e, bool v, std::string o) : algo1(e)
		{
			verbose = v;
			outp = o;
		}
		algo1(env & e);
		
		void generateSolution() override;
};

#endif