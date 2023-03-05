#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "../include/utils.h"

#define MAX_PATH 100

void get_mypwd()
{
  char *pwd = getenv("CWD");
  if (pwd == NULL)
  {
    pwd = getenv("PWD");
  }
  printf("%s\n", pwd);
}

void execute_mycd(tokenlist *tokens)
{
  /**
   * @brief This method implements changing the directory in the shell
   * prevPath and currPath are local variables.
   * It contains the last and new directories while executing the chdir().
   * LWD and CWD are set as environment variables,
   * so the prompt feature can fetch the current working directory with ease.
   */

  char prevPath[MAX_PATH];
  char currPath[MAX_PATH];
  getcwd(prevPath, MAX_PATH); // load the current path to prevPath

char *path = getenv("HOME");
  if ((tokens->size == 1) || ((tokens->size > 1) && (strcmp("$HOME", tokens->items[1]) == 0)))
  {
    /*
     * If user enters only cd, than the directory will be changed to $HOME.
     */
    if (chdir(path) != 0)
    {
      perror("Error ");
    }
  }
  else if (tokens->size >= 3)
  {
    /*
     * cd argument takes not more than one argument i.e. cd [args] or cd
     */
    perror("Invalid command ");
  }
  else
  {
    if (strcmp("-", tokens->items[1]) == 0)
    {
      /*
       * If user enters "cd -" than shell should get back to the previous working directory.
       * This if conditions does this fucntionaly by fetching the LWD variable from environment.
       */
      if (chdir(getenv("LWD")) != 0)
      {
        perror("Error ");
      }
    }
    else if (strncmp("~", tokens->items[1], 1) == 0)
    {
      char *newpath = (char*)malloc(strlen(path)+strlen(tokens->items[1]));
      strcpy(newpath, path);
      strcat(newpath, &tokens->items[1][1]);
      if (chdir(newpath) != 0)
      {
        perror("Error ");
      }
    }
    else if (chdir(tokens->items[1]) != 0)
    {
      perror("Error ");
    }
  }

  /*
   * Update the currPath and env variabels.
   */
  getcwd(currPath, MAX_PATH);
  setenv("LWD", prevPath, 1);
  setenv("CWD", currPath, 1);
}
