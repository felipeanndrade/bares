#ifndef EXP_H_
#define EXP_H_
#include <iostream>
#include <sstream>
#include <vector>
#include "error.hpp"

// Symbols needed
enum symbols_t{
/* Implementation {{{*/
	TS_PLUS 	= '+',			//!< code for "+"
	TS_MINUS 	= '-',			//!< code for "-"
	TS_MULTI 	= '*',
	TS_DIV		= '/',
	TS_MOD		= '%',
	TS_ZERO		= '0',			//!< code for "0"
	TS_NON_ZERO_DIGIT,			//!< code for digits "1"->"9"
	TS_WS		= ' ',			//!< code for a white-space
	TS_TAB		= '	',			//!< code for tab
	TS_EOS,						//!< code for "End Of String"
	TS_INVALID					//!< invalid token
};
/*}}}*/

class Exp {
/* Class implementation {{{*/
private:
/* Private members {{{*/

	class Token{
	/* Token class {{{*/
	public:
		std::string m_value;
		int m_priority;
	};
	/*}}}*/

	std::string orig_exp;
	std::vector<Token> work_exp;

/*}}}*/

public:
/* Special functions {{{*/
	Exp( std::string ); 	// Default constructor that takes a std::string obj	
	~Exp( void );			// Default destructor
/*}}}*/

/* Iterators {{{*/
	std::string::iterator begin( void );				// Returns a begin it
	std::string::iterator end( void );					// Returns a end it
	std::string::const_iterator cbegin( void ) const;	// Returns a const begin
	std::string::const_iterator cend( void ) const;		// Returns a const end
/*}}}*/

/* Operator overload {{{*/
	
	char operator[]( size_t ); // If we need direct acess to the string
/*}}}*/

/* Useful methods {{{*/
	void print( void );			// Simply print the expression (debug)
/*}}}*/

/* Parse methods {{{*/
	bool isDigit( char );				// Checks if a number is a digit or not
	bool isOperation( char );			// Checks if is a operation char
	bool isDelimiter( char );			// Checks if is a delimeter char
	bool checkParent( void );			// Check the parentheses

	int make_num( std::string::iterator &pos );	// Make the correct integer
	bool parse( void );							// Checks if the exp is valid

/*}}}*/

/* Token Methods {{{*/
	void tokenize( void );			// Tokenize the expression
	int prior( char );
	void print_t( void );
/*}}}*/
};
/*}}}*/

#endif
