#include "exp.hpp"

#define exp_debug false
#define postfix false
#define debug_token false

/* Special functions {{{*/
Exp::Exp( std::string expression ){
/* Function implementation {{{*/
	this->orig_exp = expression;
}
/*}}}*/

Exp::~Exp( void ){ /* default */ }
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

Exp::Token &Exp::Token::operator=( const Exp::Token &rhs ){
	this->m_value = rhs.m_value;
	this->m_priority = rhs.m_priority;
	return *this;
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

bool Exp::isDigit( char c_ ){
/* Function implementation {{{*/
	if( (c_ >= '0' and c_ <= '9')/*  or ( c_ == '-' )  */)
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

bool Exp::isSpace( char c_ ){
/* Function implementation {{{*/
	if( c_ == TS_WS or c_ == TS_TAB ){
		return true;
	} else {
		return false;
	}
}
/*}}}*/

bool Exp::checkParent( void ){
/* Function implementation {{{*/
	std::string brackets_t = "[]{}()";
	int pairs[6] = { 0, 0, 0, 0, 0, 0 };

	// Count the parentheses
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
			std::cout << this->orig_exp.length();
			std::cout << ")!" << std::endl;
			return 1;
		}
	}
	return 0;
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

bool Exp::hasBigger( Token top_t, Token act_t ){
/* Function implementation {{{*/
	if( act_t.m_priority >= top_t.m_priority ){
		return false;
	} else {
		return true;
	}
}
/*}}}*/

bool Exp::isOpenDel( Token top_t ){
/* Function Implementation {{{*/
	if( top_t.m_value == "(" or top_t.m_value == "[" or top_t.m_value == "{" ){
		return true;
	} else {
		return false;
	}
}
/*}}}*/

bool Exp::isClosDel( Token top_t ){
/* Function Implementation {{{*/
	if( top_t.m_value == ")" or top_t.m_value == "]" or top_t.m_value == "}" ){
		return true;
	} else {
		return false;
	}
}
/*}}}*/

void Exp::print_t( void ){
/* Function implementation {{{*/
	// std::cout << "Entered in print_t\n";
	for( auto &i : work_exp ){
		std::cout << "< " << i.m_value << ", " << i.m_priority << " > ";
	}
	std::cout << std::endl;
}
/*}}}*/

void Exp::invert_it( Token &num ){
/* Function implementation {{{*/
	int n = std::stoi(num.m_value);
	n *= -1;
	num.m_value = std::to_string(n);
}
/*}}}*/

/*}}}*/

/* Parse methods {{{*/
bool Exp::parse( void ){
/* Function implementation {{{*/
	// If the user enter a null expression
	if( !orig_exp.length() ){
		std::cout << "You entered a null expression, try again." << std::endl;
		return 1;
	}

	// If we got a missing parenthesis
	if( checkParent() ){
		return 1;
	}

	for( auto i = orig_exp.begin(); i < orig_exp.end(); i++) {
		if( isDigit(*i) ){
			make_num(i);
		} else if ( *i != TS_WS and *i != TS_TAB ){
			if( !isOperation(*i) and !isDelimiter(*i) ){
				// If isn't a delimiter neither a operation
				std::cout << "Ill formed integer at column (";
				std::cout << i - orig_exp.begin() + 1;
				std::cout << ")!" << std::endl;
				return 1;
			}
		}
	}
	return 0;			// returns success on parsing
}
/*}}}*/

long long int Exp::make_num( std::string::iterator &pos ){
	/* Function implementation {{{*/
	std::string num;

	while( isDigit(*pos) ){
		num.push_back(*pos);	
		pos++;
	}

	pos--;

	return std::stoll(num);
}
/*}}}*/

/*}}}*/

/* Token methods {{{*/
void Exp::tokenize( void ){
/* Function implementation {{{*/
	bool minus_f = false;
	for( auto c_ = orig_exp.begin(); c_ < orig_exp.end(); c_++ ){
		// for loop to get all the chars on the original expression
		if( *c_ != TS_WS and *c_ != TS_TAB ){
			// with this if statement, we will pass on all whitespaces and only
			// process what matters
			Token buf;
			if( isDelimiter( *c_ ) ){
				// is a delimiter
				buf.m_value = *c_;
				buf.m_priority = 4;
			} else if( isOperation( *c_ ) ){
				// its a operator
				if( !isDigit( *(c_-1)) and *c_ == TS_MINUS and isDigit(*(c_+1)) ){
					minus_f = true;
					c_++;
					buf.m_priority = prior( *c_ );
					long long int number = make_num( c_ );
					buf.m_value += std::to_string( number*-1 );
					// std::cout << buf.m_value << std::endl;
				} else {
					buf.m_value = *c_;
					buf.m_priority = prior( *c_ );
				}
			} else if( isDigit( *c_ ) ){
				// its a number
				long long int number = make_num( c_ );
				buf.m_value = std::to_string(number);
				buf.m_priority = 0;
			}
			// here we already should have a fully capable Token object
			// with the correct m_value and m_priority
			work_exp.push_back(buf);
		}
	}
	if( debug_token ) print_t();
}
/*}}}*/

void Exp::evaluate_token( void ){
	/* Function implementation {{{*/
	// For loop to check errors on the semanthics and correct some errors
	for( auto token = work_exp.begin(); token != work_exp.end(); token++ ){
		if( exp_debug ){
			std::cout << "Token: [" << (*token).m_value << ", ";
			std::cout << (*token).m_priority << "]" << std::endl;
		}


	}		
}
/*}}}*/

void Exp::toPostfix( void ){
/* Function implementation {{{*/
	sc::stack<Token> r_stack;		// Stack to store the operations

	for( auto &i : this->work_exp ){
		if( i.m_priority == 0 ) {
			// if the element priority is 0, then it's an integer
			postfix_e.push_back(i);
		} else if( i.m_priority > 0 and i.m_priority < 4 ) {
			// else, its a operator / delimiter
			while( !r_stack.empty() and hasBigger( r_stack.top(), i ) 
					and !isOpenDel( r_stack.top() ) )
			{
				// so, we check into the stack for bigger elements that's not 
				// opening delimiters and clean them up pushing direcly to the
				// final postfix expression
				postfix_e.push_back( r_stack.top() );	// push the top elem
				r_stack.pop();							// then, pop it
			}

			// then, adds the current operator to the stack
			r_stack.push(i);

		} else if( isOpenDel(i) ) {
			// if its a opening delimiter char...
			r_stack.push(i);
		} else if( isClosDel(i) ) {
			// if its a closing delimiter char, we can solve all the pendent
			// operations on stack until a opening delimiter char
			while( !r_stack.empty() and !isOpenDel(r_stack.top()) ){
				postfix_e.push_back(r_stack.top());
				r_stack.pop();
			}

			r_stack.pop();	// pop one more time, to consume the opening char
		}
	}	

	while(!r_stack.empty()) {
		// now, we can put all the pendent operations on the postfix expression
		if( !isOpenDel(r_stack.top()) and !isClosDel(r_stack.top()) ){
			// we wont put the delimiters on the postfix expressions, since we
			// dont need it
			postfix_e.push_back( r_stack.top() );
		}

		r_stack.pop();
	}

	if( postfix ){
		std::cout << ">>> INFIX->POSTFIX: ";
		std::cout << "\e[2m|\e[0m ";
		for( auto &c : postfix_e ){
			if( c.m_priority > 0 ){
				std::cout << "\e[1;33m";
			}
			std::cout << c.m_value << "\e[0m" << " \e[2m|\e[0m ";
		}
		std::cout << std::endl;
	}
}
/*}}}*/

/*}}}*/

/* Solving methods {{{*/
std::pair<long int, bool> Exp::solve( void ){
	/* Function implementation {{{*/
	// to solve a postfix expression, we just need to find the first operator
	// and get his position (ex: i), then we substitute i, i-1, i-2 positions
	// with the result, then, do the process again until nothing lefts

	sc::stack<Token> numbers;
	bool error_flag = false;		// Error flag
	
	for( auto &i : postfix_e ){
		if( i.m_priority == 0 ){
			numbers.push(i);
		} else if( i.m_priority > 0 and i.m_priority < 4 ){
			if( numbers.size() >= 2 ){
				// Prevents from getting segfault
				Token num1 = numbers.top(); numbers.pop();
				Token num2 = numbers.top(); numbers.pop();
				
				std::pair<Token, bool> buf( resultOf(num2, num1, i) );

				if( buf.second ){
					error_flag = true;
					break;
				} else {
					Token result = buf.first;
					numbers.push(result);
				}

			} else if (numbers.size() == 1){
				Token buf;
				Token num1 = numbers.top(); numbers.pop();

				std::pair<Token, bool> buf2( resultOf(num1, i, buf) );
				
				if( buf2.second ){
					error_flag = true;
					break;
				} else {
					Token result = buf2.first;
					numbers.push(result);
				}
			}
		}
	}

	Token f_res;
	if( error_flag ){
		return std::pair<int,bool>(0, error_flag);
	}
	else{
		f_res = numbers.top();
		long int buf_s = std::stol(f_res.m_value);
		return std::pair<int,bool>(buf_s, error_flag );
	}
}
/*}}}*/

std::pair<Exp::Token, bool> Exp::resultOf( Token num1, Token num2, Token op ){
/* Function implementation {{{*/
	long int n1 = std::stol(num1.m_value);
	long int n2;

	if( num2.m_priority != 0 ){
		// Little hack for when we got only one number and one operation
		// ex: 3 -
		op.m_value = "*";
		if( num2.m_value == "-" ){
			n2 = -1;
		} else {
			n2 = 1;
		}
	} else {
		n2 = std::stol(num2.m_value);
	}

	Token res_t;					// Temp token, when we have < 2 numbers
	bool error_flag = false;		// Error flag
	res_t.m_priority = 0;			// pseudo priority

	switch( op.m_value[0] ){
		case '+':
			if( n1 + n2 > 32767 or n1 + n2 < -32768 ){
				std::cout << "Numeric overflow error!" << std::endl;
				error_flag = true;
			} else {
				res_t.m_value = std::to_string(n1+n2);	// if everything is OK
			}
			break;

		case '-':
			if( n1 - n2 > 32767 or n1 - n2 < -32768 ){
				std::cout << "Numeric overflow error!" << std::endl;
				error_flag = true;
			} else {
				res_t.m_value = std::to_string(n1-n2);	// if everything is OK
			}
			break;

		case '*':
			if( n1 * n2 > 32767 or n1 * n2 < -32768 ){
				std::cout << "Numeric overflow error!" << std::endl;
				error_flag = true;
			} else {
				res_t.m_value = std::to_string(n1*n2);	// if everything is OK
			}
			break;

		case '/':
			if( n2 == 0 or n1 == 0 ){
				std::cout << "Division by zero!" << std::endl;
				error_flag = true;
			} else if( n1 / n2 > 32767 or n1 / n2 < -32768 ){
				std::cout << "Numeric overflow error!" << std::endl;
				error_flag = true;
			} else {
				res_t.m_value = std::to_string(n1/n2);	// if everything is OK
			}
			break;

		case '%':
			if( n2 == 0 or n1 == 0 ){
				std::cout << "Division by zero!" << std::endl;
				error_flag = true;
				break;
			} else if( n1 % n2 > 32767 or n1 % n2 < -32767 ){
				std::cout << "Numeric overflow error!" << std::endl;
				error_flag = true;
			} else {
				res_t.m_value = std::to_string(n1 % n2); // if everything is OK
			}
			break;

		case '^':
			if( pow(n1, n2) > 32767 or pow(n1, n2) < -32768 ){
				std::cout << "Numeric overflow error!" << std::endl;
				error_flag = true;
			} else {
				res_t.m_value = std::to_string(pow(n1, n2)); // if everything OK
			}
			break;
		default:
			std::cout << "Extraneous symbol after valid expression found!\n";
	}	

	return std::pair<Token, bool> (res_t, error_flag);
}

/*}}}*/

/*}}}*/
