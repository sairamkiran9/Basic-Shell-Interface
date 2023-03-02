#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include "utils.h"

tokenlist *new_tokenlist(void)
{
    tokenlist *tokens = (tokenlist *)malloc(sizeof(tokenlist));
    tokens->size = 0;
    tokens->items = (char **)malloc(sizeof(char *));
    tokens->items[0] = NULL; /* make NULL terminated */
    return tokens;
}

void add_token(tokenlist *tokens, char *item)
{
    int i = tokens->size;
    char *eol = strchr(item, '\n');
    if (eol != NULL)
    {
        item[strcspn(item, "\n")] = '\0';
    }
    tokens->items = (char **)realloc(tokens->items, (i + 2) * sizeof(char *));
    tokens->items[i] = (char *)malloc(strlen(item) + 1);
    tokens->items[i + 1] = NULL;
    if (strcmp(item, "&") != 0)
    {
        strcpy(tokens->items[i], item);
        tokens->size += 1;
    }
}

tokenlist *get_tokens(char *input, char *delimiter)
{
    char *buf = (char *)malloc(strlen(input) + 1);
    strcpy(buf, input);

    tokenlist *tokens = new_tokenlist();

    char *tok = strtok(buf, delimiter);
    while (tok != NULL)
    {
        add_token(tokens, tok);
        tok = strtok(NULL, delimiter);
    }
    free(buf);
    return tokens;
}

void free_tokens(tokenlist *tokens)
{
    for (int i = 0; i < tokens->size; i++)
    {
        free(tokens->items[i]);
    }
    free(tokens->items);
    free(tokens);
}

void print_tokens(tokenlist *tokens)
{
    for (int i = 0; i < tokens->size; i++)
    {
        printf("token %d: (%s) \n", i, tokens->items[i]);
    }
}

void execute_binaries(tokenlist *args)
{
    // print_tokens(args);
    int status = 0;
    char *path = (char *)malloc(strlen(binaries_path) + strlen(args->items[0]) + 1);

    strcpy(path, binaries_path);
    strcat(path, "/");
    strcat(path, args->items[0]);

    int pid = fork();

    if (pid < 0)
    {
        fprintf(stderr, "Failed to fork the process\n");
        exit(1);
    }
    else if (pid == 0)
    {
        /* Execute linux command */
        execv(path, args->items);
        fprintf(stderr, "%s command not found\n", args->items[0]);
        exit(1);
    }
    else
    {
        /* Wait for child process to terminate */
        waitpid(pid, &status, 0);
    }
}

void execute_builtins(tokenlist *args)
{
    int status = 0;
    int pid = fork();

    if (pid < 0)
    {
        fprintf(stderr, "Failed to fork the process\n");
        exit(1);
    }
    else if (pid == 0)
    {
        /* Execute linux command */
        execvp(args->items[0], args->items);
        fprintf(stderr, "%s command not found\n", args->items[0]);
        exit(1);
    }
    else
    {
        /* Wait for child process to terminate */
        waitpid(pid, &status, 0);
    }
}
