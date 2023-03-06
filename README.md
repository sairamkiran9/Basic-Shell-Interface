### Project 2: A Simple Unix Systems Toolkit

#### Project Statement: 
Develop a simple Unix systems toolkit for process and filesystem management

#### Project Objectives: 
Practicing Unix system calls, understanding Unix process management, synchronization, and inter-process communication (IPC), and filesystem management.

#### Project folder structure
    .
    ├── Makefile
    ├── README.md
    ├── bin
    │   ├── mymtimes.x
    │   ├── mytime.x
    │   └── mytree.x
    ├── include
    │   └── utils.h
    └── src
        ├── fileio.c
        ├── main.c
        ├── mycmds.c
        ├── mytimeout.c
        ├── pipe.c
        ├── toolkit.c
        └── utils.c

#### Makefile instructions
- `make` will create two binaries.
    - mytoolkit.x on the current directory.
    - mytimeout.x inside bin folder of the current directory.

- `make clean` will remove mytoolkit.x and mytimeout.x binaries.

#### Steps to execute
- After executing `make` and `./mytoolkit.x`
- To run and test binaries of project 1 inside the toolkit.
    - For mytree: `mytree.x [dir]`
    - For mytime: `mytime.x cmd [args]`
    - For mymtimes: `mymtimes.x [dir]`
- Example usage to run and test mytimeout inside the toolkit.
    1. `mytimeout.x 1 mytree.x /`
    2. `mytimeout.x 1 sleep 5`
- Remaing all commands can be executed like in a normal bash shell.
- The toolkit supports single pipe, multipipe and IOredirection.
