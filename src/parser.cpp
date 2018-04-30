#include "parser.hpp"

/*!
 * \brief Insert an element into the list
 * \param const size_type number : The number that will be inserted on the pile
 */
void Expression::insert( const size_type number ){
	exp_list.push_back( number );
}

/*!
 * \brief Runs the specified operation on the last two numbers on the pile
 * \param const char op : specified operation that will be executed
 */
size_type Expression::run_operation( const char op ){
	// common use variables{{{
	size_t m_size = exp_list.size();
	if( m_size < 2 ){
		// that means the list is kind of empty
		return 0;
	}

	// last two elements
	size_type e1 = exp_list[ m_size - 2 ];
	size_type e2 = exp_list[ m_size - 1 ];

	// there are basically four operations covered in here	
	if( op == '+' ){
		return e1 + e2;
	}
	else if( op == '-' ){
		return e1 - e2;
	}
	else if( op == '*' ){
		return e1 * e2;
	}
	else if( op == '/' ){
		if( e2 != 0 ){
			return e1 / e2;
		} else {
			return 0;
		}
	}
	else{
		return pow( e1, e2 );
	}/*}}}*/
}
