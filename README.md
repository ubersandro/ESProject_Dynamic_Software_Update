# Dynamic Software Update (Embedded Systems)

## Embedded Systems course (Politecnico di Milano, fall '22)  

This repository hosts the code related to the development project "Dynamic Software Update", aimed at investigating the challenges and 
the feasibility of dynamic software routines upgrades on embedded systems.   

RATIONALE 
The application runs as a big loop. At each step, the availability of an update is checked. If any, updates are applied using a utility which just replaces the current shared object with a new one. 


## NOTES
1st version: the loop cannot change, only the code of the called functions and the state of the application can change. 
possible 2nd version: one library for the loop, another for the code of the called functions (independent from each other?)


## PROBLEMS 
- I have to make application specific routines independent of the particular struct definition 
