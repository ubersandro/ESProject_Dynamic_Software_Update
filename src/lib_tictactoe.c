#include "tictactoe.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct board
{
    unsigned short int size;        
    unsigned short int player_turn; 
    unsigned short int game_over;
    unsigned short int update_ready;
    int board[3][3];
};

typedef struct board *board;
board b;

void game()
{
    while (!b->game_over)
    {
        print_board(b);
        move(b);
        stopping_point(b);
    }
}

void init_board()
{
    b->size = 3;
    b->player_turn = floor(rand() / RAND_MAX) > 0.5;
}

void move()
{
    printf("Player %d, do your move!!!\n", b->player_turn);
    unsigned int r, c;

    do
    {
        puts("r > ");
        scanf("%d", &r);
        puts("c > ");
        scanf("%d", &c);
    } while (!checks(r, c));

    b->board[r][c] = b->player_turn;

    if (check_game(b) >= 0)
    {
        b->game_over = 1;
        puts("GAME OVER!\n");
    }
    else
        b->player_turn = !b->player_turn;
}

int check_game()
{
    for (int i = 0; i < b->size; i++)
        for (int j = 0; j < b->size; j++)
        {
            if (rows_check(i, j))
                return b->player_turn;
            switch (i)
            {
            case 0: // first row
                if (j == 0 && diagonal_check(i, j))
                    return b->player_turn;
                if (j == 2 && antidiagonal_check(i, j))
                    return b->player_turn;
                break;
            case 2: // last row
                if (j == 2 && diagonal_check(i, j))
                    return b->player_turn;
                if (j == 0 && antidiagonal_check(i, j))
                    return b->player_turn;
                break;
            }
        } // for j

    return -1;
}

void print_board()
{
    for (int r = 0; r < b->size; r++)
    {
        for (int c = 0; c < b->size; c++)
        {
            switch (b->board[r][c])
            {
            case 0:
                printf("O\t|");
                break;
            case -1:
                printf(" \t|");
                break;
            default:
                printf("X\t|");
            }
        }
        puts("\n");
        // puts("\n\t|\t|\t|");
    }
}

int checks(int r, int c)
{
    if (r > 2 || c > 2)
        return 0;
    if (b->board[r][c] >= 0)
        return 0;
    return 1;
}

int diagonal_check(int r, int c)
{
    for (int i = 0; i < b->size; i++)
        if (b->board[i][i] != b->player_turn)
            return 0;
    return 1;
}

int antidiagonal_check(int r, int c)
{
    for (int i = 0; i < b->size; i++)
        if (b->board[i][b->size - 1 - i] != b->player_turn)
            return 0;
    return 1;
}
int rows_check(int r, int c)
{
    int rows = 1, cols = 1;
    ;
    for (int i = 0; i < b->size; i++)
        if (b->board[i][c] != b->player_turn)
            rows = 0;
    for (int i = 0; i < b->size; i++)
        if (b->board[r][i] != b->player_turn)
            cols = 0;
    return cols || rows;
}
