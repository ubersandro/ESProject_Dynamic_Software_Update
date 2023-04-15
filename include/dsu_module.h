/**
 * This function changes the state after an update in such a way that consistency is granted. 
*/
void * state_change(void * old_state); 

/**
 * Program memory might be dumped to a file in order to stay safe. 
*/
void backup(); 

/**
 * After a failure, restore the old code. How can a failure be checked? 
*/
void restore(); 



