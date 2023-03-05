BINS = shell
C = gcc
CFLAGS = -std=gnu99 -Wall -pedantic -g

all: $(BINS)

shell: mytoolkit.x mytimeout.x

#files included for toolkit execution
mytoolkit.x: src/main.c src/utils.c src/pipe.c src/toolkit.c src/mycmds.c src/fileio.c
	$(C) $(CFLAGS) -o mytoolkit.x src/main.c src/utils.c src/pipe.c src/toolkit.c src/mycmds.c src/fileio.c

mytimeout.x: src/mytimeout.c
	$(C) $(CFLAGS) -o ./bin/mytimeout.x src/mytimeout.c


#removes (cleans) executables
clean:
	rm mytoolkit.x
	rm ./bin/mytimeout.x	

