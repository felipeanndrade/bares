# BARES Project
Basic Arithmetic Expression Evaluator based on Stacks

# Objectives
This project consists on the implementation of a simple expression calculator
using concepts of stack and array in a real context application.

The program needs to be able to recieve simple arithmetic expressions made of:
+ Numeric constants (-32.768 to 32.767)
+ Operators ('+', '-', '/', '*', '^', '%'), with their correspondant precedence
+ Parentheses

# Dependencies

You need `git` to clone the repository, `make` and `g++` to compile the program.
To install these dependencies, you just have to use your package manager, such as a debian based distro:

`sudo apt-get install g++ git make`

# Compile

Clone the repository, and change directory:

`git clone https://github.com/felpsisonfire/bares.git`
`cd bares`

And execute `make` to compile the program.

# Execute
You have three options to execute the `bares`

Reading and writing expressions with archive stream

` ./bares input_file [output_file]`
or
`./bares < input_file > [output_file]`

And even execute and type successively expressions ended by `enter`  and then press `ctrl-d` to stop reading and show the results.

# Authorship
This program was made by [Felipe Ramos](https://github.com/FelipeCRamos) and [Felipe Andrade](https://github.com/felspsisonfire) with MIT License, for Programming Language I discipline, from Computer Science Course on [Federal University of Rio Grande do Norte](https://ufrn.br).


