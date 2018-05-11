#include "exp.hpp"

#define debug false

/* Special functions {{{*/
Exp::Exp( std::string expression ){
/* Function implementation {{{*/
	this->orig_exp = expression;
}
/*}}}*/

Exp::~Exp( void ){
	// Default destructor
}
/*}}}*/

/* Iterators {{{*/

std::string::iterator Exp::begin( void ){
	return this->orig_exp.begin();
}
std::string::const_iterator Exp::cbegin( void ) const{
	return this->orig_exp.cbegin();
}
std::string::iterator Exp::end( void ){
	return this->orig_exp.end();
}
std::string::const_iterator Exp::cend( void ) const{
	return this->orig_exp.cend();
}
/*}}}*/

/* Operator overloads {{{*/
char Exp::operator[]( size_t pos ){
	return this->orig_exp[pos];
}
/*}}}*/

/* Useful methods {{{*/
void Exp::print( void ){
/* Function implementation {{{*/
	for( auto &i : this->orig_exp ){
		if( i != ' ' and i != '	' )
			std::cout << i;
	}	
}
/*}}}*/

/*}}}*/

/* Parse methods {{{*/
bool Exp::parse( void ){
/* Function implementation {{{*/
	// If the user enter a null expression
	if( !orig_exp.length() ){
		ERR_MSG( "You entered a null expression, try again." );
		return 0;
	}

	if( !checkParent() ){
		if(debug) std::cout << "checkParent() returned 0;\n";
		return 0;
	}

	for( auto i = orig_exp.begin(); i < orig_exp.end(); i++) {
		if( isDigit(*i) ){
			make_num(i);
		} else if ( *i != TS_WS and *i != TS_TAB ){
			if( isOperation( *i ) ){
				if(debug) std::cout << "Operator: " << *i << std::endl;
			} else if( isDelimiter( *i ) ){
				if(debug) std::cout << "Delimiter: " << *i << std::endl;
			} else {
				std::cout << "Ill formed integer at column (";
				std::cout << i - orig_exp.begin() + 1;
				std::cout << ")!" << std::endl;
				return 0;
			}
		}
	}
	return 1;
}
/*}}}*/

int Exp::make_num( std::string::iterator &pos ){
/* Function implementation {{{*/
	std::string num;
	while( isDigit(*pos) ){
		num.push_back(*pos);	
		pos++;
	}
	pos--;
	if(debug) std::cout << "Number: " << num << std::endl;
	return std::stoi( num );
}
/*}}}*/

bool Exp::isDigit( char c_ ){
/* Function implementation {{{*/
	if( c_ >= '0' and c_ <= '9' )
		return true;
	else
		return false;
}
/*}}}*/

bool Exp::isOperation( char c_ ){
/* Function implementation {{{*/
	std::string list_operators = "+-*/%^";
	for( auto &i : list_operators ){
		if( c_ == i ) return true;
	}
	return false;
}
/*}}}*/

bool Exp::isDelimiter( char c_ ){
/* Function implementation {{{*/
	std::string list_delimiters = "()[]{}";
	for( auto &i : list_delimiters ){
		if( c_ == i ) return true;
	}
	return false;
}
/*}}}*/

bool Exp::checkParent( void ){
/* Function implementation {{{*/
	std::string brackets_t = "[]{}()";
	int pairs[6] = { 0, 0, 0, 0, 0, 0 };

	for( auto &i : this->orig_exp ){
		switch(i){
			case '(': pairs[0]++; break; 
			case ')': pairs[1]++; break; 
			case '[': pairs[2]++; break; 
			case ']': pairs[3]++; break; 
			case '{': pairs[4]++; break; 
			case '}': pairs[5]++; break; 
		}	
	}
	int col = 0;	// Placeholder for future upgrade
	for( int i = 0; i < 3; i+=2 ){
		if( pairs[i] != pairs[i+1] ){
			// if ever gets in here, a delimiter is missing
			std::cout << "Missing ";

			if( pairs[i] > pairs[i+1] ){
				// we miss a closing bracket
				std::cout << "closing ";
				switch(i){
					case 0:		std::cout << "\")\""; break;
					case 2:		std::cout << "\"]\""; break;
					case 4:		std::cout << "\"}\""; break;
				}
			} else {
				// we miss a opening bracket
				std::cout << "opening ";
				switch(i){
					case 0:		std::cout << "\"(\""; break;
					case 2:		std::cout << "\"[\""; break;
					case 4:		std::cout << "\"{\""; break;
				}
			}

			std::cout << " at column (";
			// TODO INNER-OUT PARENTHESES -> 5 + (3 + 2 + 2 + [2 + 3)]
			std::cout << ")!" << std::endl;
			return 0;
		}
	}
	return 1;
}
/*}}}*/
/*}}}*/

/* Token methods {{{*/
void Exp::tokenize( void ){
/* Function implementation {{{*/
	for( auto c_ = orig_exp.begin(); c_ < orig_exp.end(); c_++ ){
		if( *c_ != TS_WS and *c_ != TS_TAB ){
			Token buf;
			if( isDelimiter( *c_ ) ){
				// is a delimiter
				buf.m_value = *c_;
				buf.m_priority = 4;
			}
			if( isOperation( *c_ ) ){
				// its a operator
				buf.m_value = *c_;
				buf.m_priority = prior( *c_ );
			} 
			if( isDigit( *c_ ) ){
				// its a number
				int number = make_num( c_ );
				buf.m_value = std::to_string(number);
				if(debug) std::cout << "Number formed: " << number << std::endl;
				buf.m_priority = 0;
			}
			work_exp.push_back(buf);
		}
	}
}
/*}}}*/

void Exp::toPostfix( void ){
	/* Function implementation {{{*/
	std::list<Token> l_stack;
	std::vector<Token> postfix_e;
	this->currentPos = work_exp.begin();
	for( auto &i : this->work_exp ){
		//
		// DEBUG PRINTS
		std::cout << "--------------------------------------------\n";
		std::cout << "Stack print: ";
		for( auto &s : l_stack ){
			std::cout << s.m_value << " ";
		}
		std::cout << std::endl;

		std::cout << "Current postfix print: ";
		for( auto &p : postfix_e ){
			std::cout << p.m_value << " ";
		}
		std::cout << std::endl;

		//
		// get token by token
		switch( i.m_priority ){
			case 0:		// integer
				postfix_e.push_back(i);	
				break;
			case 1:		// +, - signs
				if( !f_check( 1 ) ){
					postfix_e.push_back(i);
				} else {
					l_stack.push_back(i);
				}
				break;
			case 2:		// *, /, % signs
				if( !f_check( 2 ) ){
					postfix_e.push_back(i);
				} else {
					l_stack.push_back(i);
				}
				break;
			case 3:		// delimiter char
				if( !f_check( 3 ) ){
					postfix_e.push_back(i);
				} else {
					l_stack.push_back(i);
				}
				break;
			// case 4:
				// delimiters, special behavior that i need to think
		this->currentPos++;
		}
	}	
	currentPos = work_exp.begin();
}
	/*}}}*/

int Exp::prior( char char_ ){
/* Function implementation {{{*/
	switch( char_ ){
		case '^': 	return 3;
		case '*': 	return 2;
		case '/': 	return 2;
		case '%': 	return 2;
		case '-': 	return 1;
		case '+': 	return 1;
	};
	return 0;
}
/*}}}*/

void Exp::print_t( void ){
/* Function implementation {{{*/
	std::cout << "Entered in print_t\n";
	for( auto &i : work_exp ){
		std::cout << "< " << i.m_value << ", " << i.m_priority << " > ";
	}
	std::cout << std::endl;
}
/*}}}*/

bool Exp::f_check( int m_prior ){
/* Function implementation {{{*/
	// Checks if it has a higher priority element (ahead)
	auto curBak( currentPos );
	for( ; currentPos < work_exp.end(); currentPos++ ){
		if ( (*currentPos).m_priority > m_prior ){
			currentPos = curBak;
			return true;
		}
	}
	currentPos = curBak;
	return false;
}
/*}}}*/

size_t Exp::peekNext( void ){
	std::vector<Token>::iterator curBak = this->currentPos;		
	return curBak++->m_priority;	
}
/*}}}*/



