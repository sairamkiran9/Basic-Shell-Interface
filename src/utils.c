#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include "../include/utils.h"

void init_path()
{
    /* adding current working dir to $PATH */
    char *binaries_path = getenv("PWD");
    char *path = getenv("PATH");
    char *new_path = (char *)malloc(strlen(path) + strlen(binaries_path) + 6);
    strcpy(new_path, path);
    strcat(new_path, ":");
    strcat(new_path, binaries_path);
    strcat(new_path, "/bin");
    setenv("PATH", new_path, 1);
    free(new_path);
}

tokenlist *new_tokenlist(void)
{
    /* intialize tokenlist structure */
    tokenlist *tokens = (tokenlist *)malloc(sizeof(tokenlist));
    tokens->size = 0;
    tokens->items = (char **)malloc(sizeof(char *));
    tokens->items[0] = NULL; /* make NULL terminated */
    return tokens;
}

void add_token(tokenlist *tokens, char *item)
{
    /* add tokens to the list array */
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
    /* Input parser based on delimeter */
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
    /* free allocated memory */
    for (int i = 0; i < tokens->size; i++)
    {
        free(tokens->items[i]);
    }
    free(tokens->items);
    free(tokens);
}

void clean_mem(tokenlist *tokens, tokenlist *args_list[])
{
  for (int i = 0; i < tokens->size; i++)
  {
    free_tokens(args_list[i]);
  }
  free_tokens(tokens);
}

void print_tokens(tokenlist *tokens)
{
    /* print parsed input arguments */
    for (int i = 0; i < tokens->size; i++)
    {
        printf("token %d: (%s) \n", i, tokens->items[i]);
    }
}

void execute_builtins(tokenlist *tokens, tokenlist *args, int index, int flag)
{
    /* check for IO redirection */
    check_fileio(tokens, args, index, flag);
    int status = 0;
    int pid = fork();

    if (pid < 0)
    {
        fprintf(stderr, "Error: fork() failed.\n");
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
