/**
 * @file fileio.c
 * @brief this method is the logic to support IOredirection
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "../include/utils.h"

void outputIO(char *outFile)
{
    /**
     * method is called when ">" character is present in the input arguments.
     * It will redirect the STDOUT to the specified file.
     *
     */
    int outFD = open(outFile, O_WRONLY | O_TRUNC | O_CREAT, 0644);
    close(1);
    dup2(outFD, 1); // stdout
    close(outFD);
}

void inputIO(char *inFile)
{
    /**
     * method is called when "<" character is present in the input arguments.
     * It will redirect the specified file content to STDIN.
     */
    if (access(inFile, F_OK))
    {
        /*
         * To check if the file or directory exists or not
         */
        perror(inFile);
        exit(0);
    }
    else
    {
        int inFD = open(inFile, O_RDONLY, 0644);
        close(0);
        dup2(inFD, 0); // stdin
        close(inFD);
    }
}

void check_fileio(tokenlist *tokens, tokenlist *args, int index, int flag)
{
    /* check for '<' or '>' present or not */
    for (int k = index; k < tokens->size; k++)
    {
        if ((strcmp(tokens->items[k], ">") == 0) || (strcmp(tokens->items[k], "<") == 0))
        {
            flag = 1;
            fileIO(k, flag, tokens); /* Call IO redirection method */
        }
        flag = 0;
    }
}

void fileIO(int index, int flag, tokenlist *tokens)
{
    /*
     * This is the main IO redirection method that handles errors and the IO redirection.
     */
    if (index + 1 < tokens->size)
    {
        if ((strcmp(tokens->items[index], ">") == 0) &&
            (tokens->items[index + 1] != NULL))
        {

            outputIO(tokens->items[index + 1]);
        }
        else if ((strcmp(tokens->items[index], "<") == 0) &&
                 (tokens->items[index + 1] != NULL))
        {
            inputIO(tokens->items[index + 1]);
        }
        else
        {
            fprintf(stderr, "syntax error near unexpected token 'newline'\n");
            exit(0);
        }
    }
    else if (flag == 1)
    {
        fprintf(stderr, "syntax error near unexpected token 'newline'\n");
        exit(0);
    }
}