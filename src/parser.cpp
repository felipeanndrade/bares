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
	/*{{{*/
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
/*}}}*/

/*!
 * 	\brief 	Converts a infix expression to postfix expression
 * 	\param 	std::string inf_exp : Infix formated expression	
 * 	\return	std::string 
 */
std::string infix_to_postfix( std::string inf_exp ){
	/*{{{*/
	// We expect that the string is already parsed (without the spaces)
	
	// Stack pile that will be used to hold operators
	std::string pos_exp;
	
	for( auto c = inf_exp.begin(); c < inf_exp.end(); c++ ){
		if( *c >= 0x30 and *c <= 0x39 ){

			int holder = 0;					// resets the holder
			size_t flag = true; 			// decimal position of the number

			while( flag == true and c < inf_exp.end() ){

				int number_size = 1;
				// Discover how many digits are
				while(*(c+number_size) >= 0x30 and *(c+number_size) <= 0x39){
					if( c + number_size++ >= inf_exp.end() ) break;
				}
				
				// Holder for future calcs
				int gen_number = 0;
				
				// Adds the 10^i * number
				for( int i = 0; i < number_size - 1; i++ ){
					int buffer = ctoi( *(c+i) );		
					gen_number += pow(10, (number_size - i - 1)) * buffer;
				}

				// Adds the number to the total number
				gen_number += ctoi(*(c + number_size - 1));

				holder = gen_number;
				
				// setting variables
				flag = false;
				c += number_size - 1;
			}

			// debug only
			std::cout << "N : " << holder << std::endl;
		} else {
			// If lands here, it's a operator sign
			int op = what_is(*c);
			std::cout << "operation " << op << std::endl;
			// TODO: Discover operations
		}
	}
	return "stub";
}
/*}}}*/

/*!
 * 	\brief 	Simplify categories telling what certain char is
 * 	\param	char el : char that will be classified
 * 	\return size_t : Char type
 */
size_t what_is( char el ){
	/* {{{
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
/*}}}*/

int ctoi( char c ){
/*{{{*/
	switch(c){
		case '0':
			return 0;
			break;
		case '1':
			return 1;
			break;
		case '2':
			return 2;
			break;
		case '3':
			return 3;
			break;
		case '4':
			return 4;
			break;
		case '5':
			return 5;
			break;
		case '6':
			return 6;
			break;
		case '7':
			return 7;
			break;
		case '8':
			return 8;
			break;
		case '9':
			return 9;
			break;
	}
	return 0;
}
/*}}}*/
