#include <iostream>
#include "parser.hpp"
#include "env.hpp"

#ifndef __GNUG__
#warning "Ten program był testowany pod kompilatorem GNU GCC 7.x"
#endif

int main(int argc, char * argv[])
{
	env Master;
	parser Parser(Master);
	Parser.parse("Sandia-Ross-2001-1.1-cln.swf");
	
	return 0;
}
