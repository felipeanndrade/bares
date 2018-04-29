RM = rm -rf

CC = g++

LIB_DIR = ./lib
INC_DIR = ./include
SRC_DIR = ./src
OBJ_DIR = ./build
BIN_DIR = ./bin
DOC_DIR = ./doc

CFLAGS = -Wall -std=c++11 -I -I$(INC_DIR)

.PHONY: all clean distclean doxy

all: $(BIN_DIR)/main

base:
	@mkdir -p $(INC_DIR)/
	@mkdir -p $(SRC_DIR)/
init:
	@mkdir -p $(BIN_DIR)/
	@mkdir -p $(OBJ_DIR)/


