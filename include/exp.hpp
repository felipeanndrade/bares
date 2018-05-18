#ifndef EXP_H_
#define EXP_H_
#include <iostream> 	// std::cout, std::cin
#include <sstream>		// stringstream
#include <list>			// std::list()
#include <cmath>		// pow()

#include "vector.hpp"	// sc::vector
#include "stack.hpp"	// sc::stack

/*!	\file 	exp.hpp
 * 	\brief 	Exp class declaration	
 * 	\author Felipe Ramos
 */

/** symbols_t variables for the char codes */
enum symbols_t{
	TS_PLUS 	= '+',			//!< code for "+"
	TS_MINUS 	= '-',			//!< code for "-"
	TS_MULTI 	= '*',			//!< code for "*"
	TS_DIV		= '/',			//!< code for "/"
	TS_MOD		= '%',			//!< code for "%"
	TS_WS		= ' ',			//!< code for a white-space
	TS_TAB		= '	'			//!< code for tab
};

/*!	\brief 	Expression class, used to store the entire expression and generate
 * 			it's result.
 */
class Exp {
/* Class implementation {{{*/
private:
/* Private members {{{*/
	/*!
	 * \brief	A small structure to store tokens value and priority.
	 */
	class Token{
	/* Token class {{{*/
	public:
		std::string m_value;		//!< Holds the value of that token
		int m_priority;				//!< Holds it's priority

		Token &operator=( const Token &rhs );
	};
	/*}}}*/

	std::string orig_exp;			//!< Will hold the original expression
	sc::Vector<Token> work_exp;		//!< Will hold the tokenized expression
	sc::Vector<Token> postfix_e;	//!< Will hold the tokenized postfixed exp
	sc::Vector<Token>::iterator currentPos = work_exp.begin();

/*}}}*/

public:
/* Special functions {{{*/
	Exp( std::string ); 	//!< Default constructor that takes a std::string obj	
	~Exp( void );			//!< Default destructor
/*}}}*/

/* Iterators {{{*/
	std::string::iterator begin( void );				//!< Returns a begin it
	std::string::iterator end( void );					//!< Returns a end it
	std::string::const_iterator cbegin( void ) const;	//!< Returns a const begin
	std::string::const_iterator cend( void ) const;		//!< Returns a const end
/*}}}*/

/* Operator overload {{{*/
	char operator[]( size_t ); //!< If we need direct acess to the string
/*}}}*/

/* Useful methods {{{*/
	// print related
	void print( void );				//!< Simply print the expression (debug)
	void print_t( void );			//!< Print the tokenized expression (debug)

	// Char related
	bool isDigit( char );			//!< Checks if a number is a digit or not
	bool isOperation( char );		//!< Checks if is a operation char
	bool isDelimiter( char );		//!< Checks if is a delimeter char
	bool isSpace( char );			//!< Checks if is a space char
	int prior( char );				//!< Tells the priority of a given char

	// Token related
	bool hasBigger( Token, Token );	//!< Tells if has a bigger priority than
	bool isOpenDel( Token );		//!< Tells if a token is a opening delimiter
	bool isClosDel( Token );		//!< Tells if a token is a closing delimiter
	void invert_it( Token & );		//!< Inverts the value
/*}}}*/

/* Parse methods {{{*/
	bool checkParent( void );					//!< Check the parentheses
	long long int make_num( std::string::iterator &pos );	//!< Make the correct integer
	bool parse( void );							//!< Checks if the exp is valid
/*}}}*/

/* Token methods {{{*/
	void tokenize( void );			//!< Tokenize the expression
	void evaluate_token( void );	//!< See if everything is correct
	void toPostfix( void );			//!< Transforms the expression to postfix
/*}}}*/

	/* Solving methods {{{*/
	std::pair<long int, bool> solve( void );				//!< Solves the postfixed exp
	std::pair<Token, bool> resultOf( Token, Token, Token );	//!< Give the result of two integers
	/*}}}*/
};
/*}}}*/

#endif
