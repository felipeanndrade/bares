#ifndef PARSER_H_
#define PARSER_H_
#include <iostream>
#include <vector>
#include <list>
#include <sstream>
#include <string>
#include <cmath>

// a function that returns the string without spaces/tabs/etc
std::string parse( std::string );

// Tells what a certain char is
size_t what_is( char el );
int ctoi( char );

#endif
