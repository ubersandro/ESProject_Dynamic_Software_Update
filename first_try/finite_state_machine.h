/**
 * The computational model on which the application is based has to be a FSM. 
 * This eases management. 
 * There are 
 * a) STATES 
 * b) FUNCTIONS 
 * Both may change. 
 * To each state we associate a bunch of application-specific actions. 
 * These actions are implemented using functions, whose code may change. 
 * The FSM has to be implemented by means of a big loop. 
 * At each step of the execution flow a state-change checking macro has to be used to figure out whether an update is required or not. 
 * Stopping points are known in advance. 
 * ?) may the "big loop" code change as well? I would say NO. 
 * 
*/