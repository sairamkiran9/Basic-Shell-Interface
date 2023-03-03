BINS = shell
C = gcc
CFLAGS = -std=gnu99 -Wall -pedantic -g

all: $(BINS)

shell: toolkit.x mytimeout.x

#files included for toolkit execution
toolkit.x: src/main.c src/utils.c src/pipe.c src/toolkit.c src/mycmds.c
	$(C) $(CFLAGS) -o toolkit.x src/main.c src/utils.c src/pipe.c src/toolkit.c src/mycmds.c

mytimeout.x: src/mytimeout.c
	$(C) $(CFLAGS) -o mytimeout.x src/mytimeout.c


#removes (cleans) executables
clean:
	rm toolkit.x
	rm mytimeout.x

