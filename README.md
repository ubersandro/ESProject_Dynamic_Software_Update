# Dynamic Software Update (Embedded Systems)

## Embedded Systems course (Politecnico di Milano, fall '22)  

This repository hosts the code related to the development project "Dynamic Software Update", aimed at investigating the challenges and 
the feasibility of dynamic software routines upgrades on embedded systems.   

## Project Description
The topic of the project is the investigation of Dynamic Software Update on Embedded Systems soft-
ware with the support of a suitable compiler. This project sets the ground for such a compiler to be
developed. In particular, an application is ran and its code is dynamically substituted preserving its
state. This way, update strategies could be easily tested and developers are provided with some hints
on how to design backend logic of the future compiler. The application running is a very simple one,
Tic Tac Toe whose state is the content of the game board.

## Design Implementation
As already stated, the application chosen to carry out the experiments is Tic Tac Toe. This latter is the core part of
the project and it has been distributed as a GNU C shared library which is the updatable module
of the application. The structure of the library, apart from game-specific routines, is described in the
header file updatable.h. The routine loop() is the application library main function, while init() and
destroy() are added for flexibility and ease of initialization/destruction of the shared library object. The
main loop executes the application specific routines (such as game actions, printing the board etc.)
, among which stopping points are located. They are the pivotal part of the updatable application
infrastructure: whenever a given action is executed (such as printing the game board, in the specific
case of this project) the application checks its state at each stopping point and, eventually, prepares for
updates if any. The macro STOPPING_POINT marks the above mentioned hooks. It basically extends
to a check of the HALT flag. HALT and UPDATE are two flags defined in the updatable.h header which
help realize dynamic update: when HALT is set to 1, loop() breaks and the UPDATE flag is set to 1. It
means that the library is ready to be swapped.
The application is built as a shared library because it is intended to be used with the Dynamic Loading
APIs. In fact, Unix-like OSes provide support for opening the library, looking up symbols (functions,
variables etc.) and eventually calling them. This is what the main.c file does. It loads the library and
starts the loop() function using the dlopen() and dlsym() routines (see GNU Linux Manual).
Besides that, main.c installs a custom handler named update_available for SIGUSR1 (user defined
signal, see GNU Linux Manual using man 7 signal): it notifies the used an update is available and sets
the HALT flag to 1 (see above). This is done in order to simulate the update available event. Upon
signal receipt, the main loop of the library application stops. In turn, the apply_update routine opens an
update facility (another shared library supposed to be distributed together with the library update itself)
and executes the state_change_transformation function in it, which takes two pointers (two handles,
one of the old version of the library and the other of the new version) and performs an update-specific
action to change the old state into the new (upon the eventual initialization of the new library). The
author of the update is in charge of writing a suitable update handler every time.
If the update is successfully applied, control is given back to the main which resolves the new loop()
symbol and restarts the application.

## Testing
Just build using 
```
make .
```
After that, run 
```
./bin/main
```
in the root folder. 
In order to simulate the "update available" event, send the UNIX signal SIGUSR1 (code `10`) to the previously spwaned process. Its PID is printed at program start on the console. This command can be used to send such a signal 
```
kill -10 PROCESS_PID
```
Beware: signal handling works in such a way that, if a signal is received while waiting for I/O, the I/O event is interrupted for signal handling. 
This means that, if a signal is received while the game loop is running with application waiting for the move position to be entered (see lib_tictactoe.c::move()) the scanf I/O event will fail. In such a case, just insert the row/column parameters for the move to be performed once again and everything will run smoothly. 
