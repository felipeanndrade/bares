#include <iostream>
#include "parser.hpp"
#define debug false

int main( int argc, char **argv ){
	// input string
	std::string input;

	while (std::getline(std::cin, input)){
		auto parsed = parse(input);
		std::cout << parsed << std::endl;
		// TODO: Treat expressions
	}

	std::cout << "Normal exit." << std::endl;
	return EXIT_SUCCESS;
}
