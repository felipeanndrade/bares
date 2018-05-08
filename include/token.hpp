#ifndef TOKEN_H_
#define TOKEN_H_
#include "parser.hpp"

class Token
{
	private:
		size_t 	m_type;				// See the parser.cpp:what_is()
		int 	m_value;			// value (if its a number)
		char 	m_oper;				// operation
	public:
		Token( int );				// Initializer for numbers
		Token( char );				// Initializer for operations

		size_t 	type( void );		// Returns the type
		int 	value( void );		// Returns the value
		char 	get_op( void );		// Returns the operation
		void 	erase( void );		// Erase current token
};


void tokenize_infix( std::string );

#endif
