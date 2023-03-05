#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include "../include/utils.h"

void init_path(){
    char *binaries_path = getenv("PWD");
    char *path = getenv("PATH");
    char *new_path = (char *)malloc(strlen(path) + strlen(binaries_path) + 6);
    strcpy(new_path, path);
    strcat(new_path, ":");
    strcat(new_path, binaries_path);
    strcat(new_path, "/bin");
    setenv("PATH",new_path, 1);
}

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

void execute_builtins(tokenlist *tokens, tokenlist *args, int index, int flag)
{
    // check_fileio(tokens, args, index, flag);
    for (int k = index; k < tokens->size; k++)
    {
        if ((strcmp(tokens->items[k], ">") == 0) || (strcmp(tokens->items[k], "<") == 0))
        {
            flag = 1;
            fileIO(k, flag, tokens); /* Call IO redirection method */
        }
        flag = 0;
    }
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
