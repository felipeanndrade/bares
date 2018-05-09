#include "error.hpp"

void ERR_MSG( std::string msg ){
/* Function implementation {{{*/
	std::cout << "\e[3m";
	std::cout << msg;
	std::cout << "\e[0m";
	std::cout << std::endl;
}
/*}}}*/
