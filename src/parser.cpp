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

	if( el == '*' or el == '/' or el == '%'){
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
