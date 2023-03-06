/**
 *@file main.c
 *@brief This file intializes mytoolkit
 *
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "../include/utils.h"

int main()
{
    /**
     * add current working directory to $PATH
     */
    init_path();
    if ((fd = fopen("/dev/tty", "r+")) == 0)
    {
        perror("Cannot open /dev/tty\n");
        exit(0);
    }
    /**
     * Intialize toolkit
     */
    init_toolkit(fd);
}