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
    /* add current working directory to $PATH */
    init_path();

    /* Intialize toolkit */
    init_toolkit();
}