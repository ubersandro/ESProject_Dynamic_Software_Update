/**
 * State shape agnostic module used to define needed game functions.
 * */ 

void print_board(); 
int check_game(); 
void move(); 
void game(); 
int checks(int r, int c); 
int antidiagonal_check(int r, int c); 
int diagonal_check(int r, int c); 
int rows_check(int r, int c); 
void init_board();