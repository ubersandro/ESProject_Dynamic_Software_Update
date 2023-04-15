#include <stdio.h> 
#include <stdlib.h> 
#include <dlfcn.h>
#include "dsu_module.h"

int main(int argc, const char * argv[]){
    // open shared library (initial version) 
    void * handle = dlopen("./lib/init.so", RTLD_LAZY);
    // MAIN LOOP
    
}

// handler of signal for available update 
int update_available(){
    // check whether ./updates is empty 
    // if not empty, call apply_update
    return 0; 
} 



