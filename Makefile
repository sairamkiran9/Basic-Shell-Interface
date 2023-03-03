BINS = shell
C = gcc
CFLAGS = -std=gnu99 -Wall -pedantic -g

all: $(BINS)

shell: toolkit.x mytimeout.x

#files included for toolkit execution
toolkit.x: main.c utils.c pipe.c toolkit.c mycmds.c
	$(C) $(CFLAGS) -o toolkit.x main.c utils.c pipe.c toolkit.c mycmds.c

mytimeout.x: mytimeout.c
	$(C) $(CFLAGS) -o mytimeout.x mytimeout.c


#removes (cleans) executables
clean:
	rm toolkit.x
	rm mytimeout.x