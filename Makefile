CC=gcc # check clang   
DIR=/home/ubersandro/espr/ESProject_Dynamic_Software_Update
BIN=$(DIR)/bin
SRC=$(DIR)/src

LIB_BIN=$(DIR)/lib
INCLUDE=include 
OPT=-Wall -O3 -I$(INCLUDE) -g 
LIB_FLAG=-shared -fPIC

all: main init.so update.so handler.so

main: include/dsu_module.h
	$(CC) $(OPT) $(SRC)/main.c -o $(BIN)/main 

init.so: include/tictactoe.h
	$(CC) $(OPT) $(LIB_FLAG) $(SRC)/lib_tictactoe.c -o $(LIB_BIN)/init.so

update.so: include/tictactoe.h
	$(CC) $(OPT) $(LIB_FLAG) $(SRC)/updates/lib_update.c -o $(SRC)/updates/update.so

handler.so: include/update_handler.h 
	$(CC) $(OPT) $(LIB_FLAG) $(SRC)/handler/handler1.c -o $(SRC)/handler/handler.so

clean: 
	rm $(BIN)/* $(LIB_BIN)/* 