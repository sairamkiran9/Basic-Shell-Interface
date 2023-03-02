
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
void execute_builtins(tokenlist *args);
void execute_binaries(tokenlist *args);
int execute_pipe(tokenlist *tokens[], int pipe_count);
void execute_single_pipe(tokenlist *cmd1, tokenlist *cmd2);
void execute_multi_pipe(tokenlist *args_list[], int pipe_count, int curr_pipe);


void get_mypwd(void);
void execute_mycd(tokenlist *tokens);