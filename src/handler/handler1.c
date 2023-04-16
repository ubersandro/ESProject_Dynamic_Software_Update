#include "update_handler.h"
#include <dlfcn.h>
#include<stdio.h>
#include <string.h>
#include<stdlib.h> 

/**
 * Testing implementation of an update handler. 
*/
struct board
{
    unsigned short int size;        
    unsigned short int player_turn; 
    unsigned short int game_over;
    int board[3][3];
};

typedef struct board *board;


// user defined actions to initialize the new handle 
void state_change_transformation(void * old_handle, void * new_handle){
    // pick old board, copy its content into new handle
    printf("HANDLER> handling update\n"); 
    board old = dlsym(old_handle, "b"); 
    board b = malloc(sizeof(struct board)); 
    memcpy(b, old, sizeof(struct board)); 
    
    // print to check data 
    printf("printing old board to check...\n"); 
    printf("%d\n", old->size); 
    for (int r = 0; r < old->size; r++)
    {
        for (int c = 0; c < old->size; c++)
        {
            printf("%d\n", b->board[r][c]); 
            switch (b->board[r][c])
            {
            case 0:
                printf("O\t><");
                break;
            case -1:
                printf(" \t><");
                break;
            default:
                printf("X\t><");
            }
        }
        puts("\n");
    }

    void (* init)() = dlsym(new_handle, "init"); 
    (*init)(); //alloc new struct 
    board new = dlsym(new_handle, "b"); 

    //  for (int r = 0; r < old->size; r++)
    // {
    //     for (int c = 0; c < old->size; c++)
    //     {
    //         new->board[r][c] = tmp->board[r][c]; 
    //     }
    // }
    memcpy(new, b, sizeof(struct board)); 
    free(b); 
    printf("HANDLER> update handled correctly\n"); 
}