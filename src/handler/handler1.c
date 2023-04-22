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
    board old = dlsym(old_handle, "x"); 

    //void (* init)() = dlsym(new_handle, "init"); 
    //(*init)(); //alloc new struct         
    board new = dlsym(new_handle, "x"); 
    printf("Copying OLD %p into NEW %p\n", old, new); 
    memcpy(new, old, sizeof(struct board)); 
    printf("HANDLER> update handled correctly\n"); 
}