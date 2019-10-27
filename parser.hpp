#ifndef _PARSER_HPP_
#define _PARSER_HPP_

class env;

class parser{
	protected:
	env& en;

	public:
	parser(env&);
	
	bool parse(const char*);
};

#endif