#include <iostream>
#include "exp.hpp"

#ifndef debug
#define debug true
#endif

int main( int argc, char **argv ){
	std::string input;
	while( std::getline(std::cin, input) ){
		Exp main_exp(input);	///> Generates the expression object
		if( main_exp.parse() ){
			// If parser returns 1, then something went wrong
			// Then, we got a error exit
			return 1;
		}

		main_exp.tokenize();	// Transforms the string exp to a token exp
		main_exp.evaluate_token();
		main_exp.toPostfix();	// Transforms the token exp to a postfix exp

		// Solves the postfix expression
		std::pair<long int,bool> res = main_exp.solve();
		
		if( !res.second )
			std::cout  << res.first << std::endl;
	}
	return EXIT_SUCCESS;
}
