#include <dlfcn.h>  

int main(int argc, char const *argv[])
{
    void * handle = dlopen("./libtest.so", RTLD_GLOBAL|RTLD_NOW); 
    void * (*function)(void *);
    function =  (void * (*) (void *)) dlsym(handle, "state_change");
    (*function)(0);   
    dlclose(handle);  
    return 0;
}
