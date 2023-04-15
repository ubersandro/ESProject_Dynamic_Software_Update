#include<stdio.h>
#include "dsu_module.h"

void * state_change(void * old_state){
    printf("hey you\n"); 
    return NULL; 
}

void backup(){
    return; 
}

void restore(){
    return; 
}
