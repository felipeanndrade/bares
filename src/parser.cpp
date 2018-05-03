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
		result += '\0';
	}
	return result;
}
