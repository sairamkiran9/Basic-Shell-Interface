BINS = toolkit
C = gcc
CFLAGS = -std=gnu99 -Wall -pedantic -g

all: $(BINS)

#files included for toolkit execution
toolkit: main.c utils.c toolkit.c mycmds.c
	$(C) $(CFLAGS) -o toolkit main.c utils.c toolkit.c mycmds.c


#removes (cleans) executables
clean:
	rm $(BINS)