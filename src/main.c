#include <stdio.h> 
#include <stdlib.h> 
#include <dlfcn.h>
#include "dsu_module.h"
#include <signal.h>

void * handle; 

int main(int argc, const char * argv[]){
    // install update signal handler 
    sigaction(SIGUSR1, update_available, NULL); 

    // open shared library (initial version) 
    handle = dlopen("./lib/init.so", RTLD_GLOBAL);
    if(!handle) fprintf(stderr, "error opening lib\n"); 
    // start app loop 
    void (* loop)() = dlsym(handle, "loop"); 

    while(1){
        (*loop)();
        // get symbol telling whether execution stopped for update or not 
        int * x = (int *) dlsym(handle, "UPDATE_READY");  
        int ready = *x; 
        if(ready) apply_update; 
        else break;    
    }

}

// handler of signal for available update 
void update_available(){
    printf("+++ UPDATE AVAILABLE +++\n"); 
    int * flag_ptr = (int *) dlsym(handle, "HALT_FLAG"); 
    *flag_ptr = 1; 
    return; 
} 

int apply_update(){
    
    return 0; 
}

