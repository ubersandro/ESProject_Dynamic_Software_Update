#include <stdio.h> 
#include <stdlib.h> 
#include <dlfcn.h>
#include "dsu_module.h"
#include <signal.h>
#include <unistd.h>

void * handle; 

int main(int argc, const char * argv[]){
    // install update signal handler 
    struct sigaction t = {0}; 
    struct sigaction s = {0}; 
    s.sa_handler = &update_available; 
    sigaction(SIGUSR1, &s, &t); 
    printf("installing update signal handler. Send signal %d to process %d to trigger update.\n", SIGUSR1, getpid()); 

    // open shared library (initial version), retrieve syms and init 
    handle = dlopen("./lib/init.so", RTLD_GLOBAL|RTLD_NOW);
    void (* loop)() = dlsym(handle, "loop"); 
    void (* init)() = dlsym(handle, "init"); 
    (*init)(); 

    //main app loop 
    while(1){
        printf("MAIN> starting main app loop\n"); 
        (*loop)(); // this function returns when the game is over or the update is ready
        
        // get symbol telling whether execution stopped for update or not 
        int * x = (int *) dlsym(handle, "UPDATE_READY");  
        int ready = *x; 
        if(ready){
            if(apply_update())
                printf("MAIN> update applied\n"); 
        }

        // else { /*TODO: handle game over case*/ 
        //     printf("DONE\n");
        //     // terminating execution, be sure everything is dealloc 
        //     void (* destroy)() = dlsym(handle, "destroy"); 
        //     (*destroy)(); 
        //     break;    
        // }
    }//while 

}

void update_available(){
    printf("+++ UPDATE AVAILABLE +++\n"); 
    int * flag_ptr = (int *) dlsym(handle, "HALT_FLAG"); 
    *flag_ptr = 1; //this triggers an exit from the lib app loop 
    return; 
} 

/**
 * NOTE: this function is supposed to handle destruction of old handle(e.g HEAP frees etc.)
*/
int apply_update(){
    dlclose(handle); 
    void * new_handle = dlopen("/home/ubersandro/espr/ESProject_Dynamic_Software_Update/src/updates/update.so", RTLD_GLOBAL| RTLD_NOW); 
    if(! new_handle){
        fprintf(stderr, "MAIN> failed to open NEW lib\n"); 
        return 0; 
    }
    void * updater_handle = dlopen("/home/ubersandro/espr/ESProject_Dynamic_Software_Update/src/handler/handler.so", RTLD_LOCAL| RTLD_NOW); 
    if(! updater_handle){
        fprintf(stderr, "MAIN> failed to open updater handle\n"); 
        return 0; 
    }

    void (*f)() = dlsym(updater_handle, "state_change_transformation"); 

    (*f) (handle, new_handle); 
    // dlclose(handle); 
    
    handle = new_handle; 
    return 1; 

    // TESTING CODE 
    /**
    dlclose(handle); 
    handle = dlopen("lib/init.so.copy", RTLD_GLOBAL| RTLD_NOW); 
    if(!handle) {
        fprintf(stderr, "failed to open .so object\n"); 
        return 0; 
    }
    void (* init)() = dlsym(handle, "init"); 
    printf("MAIN> initializing new library after the loading\n"); 
    (*init)(); 
    return 1; 
    */
    
}

