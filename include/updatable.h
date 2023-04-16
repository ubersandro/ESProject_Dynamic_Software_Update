
/**
 * DSU-related structures
 * They are on the compiler, I am integrating them here just to have an idea of how to realize DSU.
*/
int HALT_FLAG; 
int UPDATE_READY; // this flag is one is the loop is stopped to prepare for an update 
#define STOPPING_POINT if(HALT_FLAG) { UPDATE_READY = 1; printf("LIB> preparing for update\n"); break; } 

void init(); 
void destroy(); 
void loop(); 