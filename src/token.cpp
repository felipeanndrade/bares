#include "token.hpp"

/* Token class {{{*/
/*!
 * 	\brief	Token constructor with an integer
 * 	\param	int value : Integer value
 */
Token::Token( int value ){
	this->m_type = 0;
	this->m_value = value;
}

/*!
 * 	\brief	Token constructor with a char
 * 	\param	char operation : Desired operation	
 */
Token::Token( char operation ){
	this->m_type = what_is(operation);
	this->m_oper = operation;
}

/*!
 * 	\brief 	A function to discover the token
 * 	\return	m_type
 */
size_t Token::type( void ){
	return this->m_type;	
}

/*!
 * 	\brief 	A function to discover the value
 * 	\return	m_value
 */
int Token::value( void ){
	return this->m_value;
}

/*!
 * 	\brief 	A function to discover the operation
 * 	\return	m_oper
 */
char Token::get_op( void ){
	return this->m_oper;
}

/*!
 * 	\brief 	A function to erase the token
 */
void Token::erase( void ){
	this->m_type = 0;
	this->m_value = 0;
	this->m_oper = '\0';
}
/*}}}*/

/* Tokenify the infix parse {{{*/
/*!
 * 	\brief 	Converts a infix expression to postfix expression
 * 	\param 	std::string inf_exp : Infix formated expression	
 * 	\return	std::string 
 */
void tokenize_infix( std::string inf_exp ){
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
			std::cout << "operation prescedence " << op << std::endl;

			// TODO: Discover operations
		}
	}
}
/*}}}*/

/*}}}*/
