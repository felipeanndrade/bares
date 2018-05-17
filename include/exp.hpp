#ifndef EXP_H_
#define EXP_H_
#include <iostream> 
#include <sstream>
// #include <vector>
#include "vector.hpp"
#include <list>
// #include <stack>
#include "stack.hpp"
#include <cmath>
#include "error.hpp"

enum symbols_t{
	TS_PLUS 	= '+',			//!< code for "+"
	TS_MINUS 	= '-',			//!< code for "-"
	TS_MULTI 	= '*',			//!< code for "*"
	TS_DIV		= '/',			//!< code for "/"
	TS_MOD		= '%',			//!< code for "%"
	TS_WS		= ' ',			//!< code for a white-space
	TS_TAB		= '	'			//!< code for tab
};

class Exp {
/* Class implementation {{{*/
private:
/* Private members {{{*/
	class Token{
	/* Token class {{{*/
	public:
		std::string m_value;
		int m_priority;

		Token &operator=( const Token &rhs );
	};
	/*}}}*/

	std::string orig_exp;
	sc::Vector<Token> work_exp;
	sc::Vector<Token> postfix_e;
	sc::Vector<Token>::iterator currentPos = work_exp.begin();

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
	// print related
	void print( void );				// Simply print the expression (debug)
	void print_t( void );			// Print the tokenized expression (debug)

	// Char related
	bool isDigit( char );			// Checks if a number is a digit or not
	bool isOperation( char );		// Checks if is a operation char
	bool isDelimiter( char );		// Checks if is a delimeter char
	bool isSpace( char );			// Checks if is a space char
	int prior( char );				// Tells the priority of a given char

	// Token related
	bool hasBigger( Token, Token );	// Tells if has a bigger priority than
	bool isOpenDel( Token );		// Tells if a token is a opening delimiter
	bool isClosDel( Token );		// Tells if a token is a closing delimiter
	void invert_it( Token & );
/*}}}*/

/* Parse methods {{{*/
	bool checkParent( void );					// Check the parentheses
	int make_num( std::string::iterator &pos );	// Make the correct integer
	bool parse( void );							// Checks if the exp is valid
/*}}}*/

/* Token methods {{{*/
	void tokenize( void );			// Tokenize the expression
	void evaluate_token( void );	// See if everything is correct
	void toPostfix( void );			// Transforms the expression to postfix
/*}}}*/

	/* Solving methods {{{*/
	int solve( void );	
	Token resultOf( Token, Token, Token );
	/*}}}*/
};
/*}}}*/

#endif
