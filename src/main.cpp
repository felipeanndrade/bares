#include <iostream>
#include "exp.hpp"
#include "error.hpp"

#define debug true

int main( int argc, char **argv ){
	std::cout << "> Program started\n";

	std::string input;

	while( std::getline(std::cin, input) ){

		Exp main_exp(input);	///> Generates the expression object
		std::cout << "E: ";
		main_exp.print();
		std::cout << std::endl;
		if( !main_exp.parse() ){
			std::cout << "> Error exit" << std::endl;
			return 0;
		}

		main_exp.tokenize();
		main_exp.print_t();
	}

	std::cout << "\n> Normal exit" << std::endl;
	return EXIT_SUCCESS;
}
