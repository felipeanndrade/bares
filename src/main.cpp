#include <iostream>
#include "exp.hpp"
#include "error.hpp"

#ifndef debug
#define debug true
#endif

int main( int argc, char **argv ){
	std::string input;
	while( std::getline(std::cin, input) ){
		Exp main_exp(input);	///> Generates the expression object
		main_exp.print();
		std::cout << std::endl;
		if( main_exp.parse() ){
			// If parser returns 1, then something went wrong
			// std::cout << "> Error exit" << std::endl;
			// Then, we got a error exit
			return EXIT_SUCCESS;
		}

		main_exp.tokenize();	// Transforms the string exp to a token exp
		main_exp.evaluate_token();
		main_exp.toPostfix();	// Transforms the token exp to a postfix exp

		int res = main_exp.solve();		// Solves the postfix expression
		std::cout << res << std::endl;
	}
	return EXIT_SUCCESS;
}
