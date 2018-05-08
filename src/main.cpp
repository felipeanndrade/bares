#include <iostream>
#include "parser.hpp"
#include "token.hpp"
#define debug true

std::string wel_msg = "Please, enter the infix expression: ";

int main( int argc, char **argv ){
	std::cout << "> Program started\n";
	// input string
	std::string input;

	if(debug) std::cout << wel_msg;
	while (std::getline(std::cin, input)){
		// The parse() generates an infix expression without spaces and tabs
		auto infix_expression = parse(input);	
		if(debug) std::cout << "Infix generated exp: " << infix_expression;
		std::cout << std::endl;
		tokenize_infix(infix_expression);
		std::cout << "Finalized" << std::endl;

		// and then, asks the user all again until EOF
		if(debug) std::cout << wel_msg;
	}

	std::cout << "EOF exit." << std::endl;
	return EXIT_SUCCESS;
}
