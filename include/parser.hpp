#ifndef PARSER_H_
#define PARSER_H_
#include <iostream>
#include <vector>
#include <list>
#include <string>

// a function that returns the string without spaces/tabs/etc
std::string parse( std::string );

// Tells what a certain char is
size_t what_is( char el );

// Converts a infix expression to postfix expression to later work
std::string infix_to_postfix( std::string );

#endif
