/**
 * This module manages the state changing transformation defined by the provider of the update. 
 * This transformation has to be well aware of both old and new shared library application and its state.  
*/

/**
 * Assumption: the name of the state variable is STATE. 
*/
void state_change_transformation(void * old_handle, void * new_handle); 