#include "dsu_module.h"

/**
 * This is my state .
*/
struct board {
    unsigned short int size; // default
    unsigned short int player_turn;  // 0 starts by default, only two players (0, !0) 
    unsigned short int game_over; 
    unsigned short int update_ready; 
    int board[3][3]; 
}; 


void print_board(struct board *); 
int check_game(struct board *); 
void move(struct board *); 
void init_board(struct board *); //board size may change, is has to be managed 

/**
 * main loop 
*/
void game(struct board *); 
void update(struct board *); 
int checks(struct board *b, int r, int c); 
int antidiagonal_check(struct board * b, int r, int c); 
int diagonal_check(struct board * b, int r, int c); 
int rows_check(struct board * b, int r, int c); 
