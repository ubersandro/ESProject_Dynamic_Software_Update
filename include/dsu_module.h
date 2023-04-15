/**
 * This module is in charge of
 * 1) detecting available updates 
 * 2) applying updates according to a special state changing function provided together with the update
*/

/**
 * - set HALT_FLAG to 1 in shared lib (this will block loop)  
 */
void update_available(); 

/**
 * This function
 * - closes the old handle 
 * - backs up the old handle
 * - replaces the old handle with the new 
 * - opens the NEW handle
 * - picks update provider defined state transformation function and applies it
 * After this chain of operations main loop execution goes on as usual. 
 * Returns 0 on success, nonzero values otherwise.
*/
int apply_update(); 