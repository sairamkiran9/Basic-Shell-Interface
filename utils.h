
typedef struct
{
    int size;
    char **items;
} tokenlist;

char *binaries_path;

tokenlist *new_tokenlist(void);
tokenlist *get_tokens(char *input, char *delimiter);
void add_token(tokenlist *tokens, char *item);
void free_tokens(tokenlist *tokens);
void print_tokens(tokenlist *tokens);

void execute_cmds(tokenlist *tokens);
void execute_pipe(tokenlist *tokens[]);
void execute_builtins(tokenlist *args);
void execute_binaries(tokenlist *args);

void get_mypwd(void);
void execute_mycd(tokenlist *tokens);