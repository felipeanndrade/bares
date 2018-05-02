#ifndef PARSER_H_
#define PARSER_H_
#include <iostream>
#include <vector>
#include <cmath>
#include <initializer_list>
#include <string>

/*TODO: 
 * Tabela de erros
 * Armazenar a lista de tokens
 * Remover espaços em branco 
 */

using size_type = int;
	
class Expression{
	private: 
		std::vector<size_type> exp_list;	
	public:
		// Constructors / Destructors
		Expression( std::initializer_list<size_type> );
		// ~Expression();

		// Inserting
		void insert( const size_type );		// Will insert an element on pile
		size_type run_operation( const char );	// Apply desired operation

		// access related
		size_type at( size_t );
		size_type operator[]( size_t );

		// debug related 
		void print();		// print current expression members
		void print( std::string ); 
		void clear();		// clear all expression members
		void size();		// get current size (number of members) of expression
};

#endif
