char buf[82];

typedef struct
{
    int size;
    char **items;
} tokenlist;

tokenlist *new_tokenlist(void);
tokenlist *get_tokens(char *input, char *delimiter);
void add_token(tokenlist *tokens, char *item);
void free_tokens(tokenlist *tokens);
void print_tokens(tokenlist *tokens);
void clean_mem(tokenlist *tokens, tokenlist *args_list[]);

void execute_cmds(tokenlist *tokens);
void execute_builtins(tokenlist *tokens, tokenlist *args, int index, int flag);
int execute_pipe(tokenlist *tokens[], int pipe_count);
void execute_single_pipe(tokenlist *cmd1, tokenlist *cmd2);
void execute_multi_pipe(tokenlist *args_list[], int pipe_count, int curr_pipe);
void fileIO(int index, int flag, tokenlist *tokens);
void check_fileio(tokenlist *tokens, tokenlist *args, int index, int flag);

void init_path(void);
void init_toolkit();
void get_mypwd(void);
void execute_mycd(tokenlist *tokens);