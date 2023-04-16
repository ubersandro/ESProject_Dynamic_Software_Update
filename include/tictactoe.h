/**
 * State shape agnostic module used to define needed game functions.
 * */ 
#include "updatable.h"

void print_board(); 
int check_game(); 
void move(); 

int checks(int r, int c); 
int antidiagonal_check(int r, int c); 
int diagonal_check(int r, int c); 
int rows_check(int r, int c); 