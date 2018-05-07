#include "parser.hpp"

/*!
 * 	\file 	parser.cpp
 * 	\author	Felipe Andrade & Felipe Ramos
 */

/*!
 * 	\brief	A parse function that will 'filter' the string removing whitespaces
 * 	\param	std::string expression : The string that needs to be filtered
 * 	\return A filtered std::string object
 */
std::string parse( std::string expression ){
	std::string result;
	for( auto i = expression.begin(); i != expression.end(); i++ ){
		switch(*i){
			case ' ':
				break;
			case '	':
				break;
			default:
				result += *i;
		}
	}
	return result;
}

/*!
 * 	\brief 	Converts a infix expression to postfix expression
 * 	\param 	std::string inf_exp : Infix formated expression	
 * 	\return	std::string 
 */
std::string infix_to_postfix( std::string inf_exp ){
	// We expect that the string is already parsed

	// Stack pile that will be used to hold operators
	std::list<char> opr_stack;
	std::string pos_exp;

	for( auto c = inf_exp.begin(); c != inf_exp.end(); c++ ){
		std::cout << "Processing char: " << *c << "\n";
		if( *c >= 0x30 and *c <= 0x39 ){
			std::cout << "\tIt's a number between [0-9]!\n";

			int holder = 0;				// resets the holder
			size_t flag = 1; 			// decimal position of the number
			while( flag != 0 and c != inf_exp.end() - 1){
				std::cout << "\t\twhile: " << *c << std::endl;
				if( *c >= 0x30 and *c <= 0x39 ){
					std::cout << "\t\t\tIt's another number!\n";
					std::cout << "\t\t\tCurrent holder = " << holder << "\n";
					int num = *c;
					std::cout << "\t\t\tNum = " << num << std::endl;
					holder += flag * int(*c);
					std::cout << "\t\t\t\t*c = " << (int)*c << std::endl;
					std::cout << "\t\t\tAfter holder = " << holder << "\n";
					flag++;
					c++;
				} else {
					std::cout << "\t\t\tIt's not another number!\n";
					flag = 0;
				}
			}
			std::cout << "\t\tPossible number: " << holder << std::endl;
		} else {
			std::cout << "\tIgnored\n";
		}
	}
}

/*!
 * 	\brief 	Simplify categories telling what certain char is
 * 	\param	char el : char that will be classified
 * 	\return size_t : Char type
 */
size_t what_is( char el ){
	/*
	 * HELP TABLE
	 * 0 : simple number
	 * 1 : add or subt operation
	 * 2 : mult or div operation
	 * 3 : exp operation
	 * 4 : parentheses
	 */
	if(    el == '(' or el == ')'
		or el == '{' or el == '}'
		or el == '[' or el == ']' ){
		return 4;
	}

	if(	el == '^' ){
		return 3;
	}

	if( el == '*' or el == '/' ){
		return 2;
	}

	if( el == '+' or el == '-' ){
		return 1;
	}

	// if didn't returned anything till now, it's a number
	return 0;
}

