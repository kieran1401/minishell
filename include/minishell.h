#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "../libft/libft.h"

# define C_DEF "\033[0;39m"
# define C_GREEN "\033[0;92m"
# define C_RED "\033[0;31m"
# define C_YELLOW "\033[0;93m"
# define C_PINK "\033[0;95m"

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_REDIRECT_APPEND,
	TOKEN_REDIRECT_HEREDOC,
	TOKEN_EOF
}	t_token_type;

typedef enum e_node_type
{
	NODE_COMMAND,
	NODE_ARGS,
	NODE_REDIRECT_IN,
	NODE_REDIRECT_OUT,
	NODE_REDIRECT_APPEND,
	NODE_REDIRECT_HEREDOC,
	NODE_PIPE,
	NODE_INVALID
}	t_node_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
}	t_token;

typedef struct s_lexer
{
	char			*input;
	size_t			pos;
	char			current_char;
	t_token			*saved_token;
}	t_lexer;

typedef struct s_redirection
{
	t_node_type				type;
	char					*filename;
	struct s_redirection	*next;
}	t_redirection;

typedef struct s_ast
{
	t_node_type		type;
	char			*value;
	t_redirection	*redirections;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_minishell
{
	int				last_exit_status;
	char			*input;
	char			**envp;
	char			**paths;
	t_env			*env_lst;
	t_lexer			*lexer;
	int				saved_stdin;
	int				saved_stdout;
}	t_minishell;

typedef struct s_pipe_state
{
	int				fd[2];
	int				saved_stdin;
	int				saved_stdout;
	pid_t			*pids;
	int				pid_count;
	int				cmd_count;
}	t_pipe_state;

typedef struct s_io_state
{
	int				in_fd;
	int				out_fd;
	int				saved_stdin;
	int				saved_stdout;
}	t_io_state;

/* Initialization */
t_minishell		*initialize_minishell(char **envp);
void			clear_minishell(t_minishell *shell);

/* Signal Handling */
void			setup_signal_handlers(void);
void			sigint_handler(int sig);

/* Input Handling */
void			handle_input(t_minishell *shell);

/* Lexer Functions */
t_lexer			*init_lexer(char *input);
t_token			*get_next_token(t_lexer *lexer, t_minishell *shell);
void			advance(t_lexer *lexer);
void			skip_whitespace(t_lexer *lexer);
t_token			*create_token(t_token_type type, char *value);
t_token			*handle_word(t_lexer *lexer, t_minishell *shell);
t_token			*handle_less_than(t_lexer *lexer);
t_token			*handle_greater_than(t_lexer *lexer);
int				handle_quotes(t_lexer *lexer, char *buffer, int pos,
					t_minishell *shell);
char			*extract_variable_name(t_lexer *lexer);
void			save_token(t_lexer *lexer, t_token *token);
t_token			*get_saved_token(t_lexer *lexer);
int				handle_word_dispatcher(t_lexer *lexer, char *buffer, int pos,
					t_minishell *shell);
int				handle_dollar(t_lexer *lexer, char *buffer, int pos,
					t_minishell *shell);
int				append_exit_status(t_lexer *lexer, char *buffer, int pos,
					t_minishell *shell);
int				append_variable(t_lexer *lexer, char *buffer, int pos,
					t_minishell *shell);
int				handle_dollar_in_quotes(t_lexer *lexer, char *buffer, int pos,
					t_minishell *shell);
int				handle_double_quotes(t_lexer *lexer, char *buffer, int pos,
					t_minishell *shell);
int				handle_single_quotes(t_lexer *lexer, char *buffer, int pos);
int				append_char_to_buffer(t_lexer *lexer, char *buffer, int pos);

/* Parser Functions */
t_ast			*ft_parser(t_minishell *shell);
t_ast			*parse_command(t_minishell *shell);
int				is_redirection(t_token_type type);
t_redirection	*create_redirection(t_minishell *shell, t_token *initial_token);
t_ast			*parse_pipeline_recursive(t_ast *left, t_minishell *shell);
t_ast			*parse_pipeline(t_minishell *shell);
t_ast			*create_ast_node(t_node_type type, char *value);
void			free_ast(t_ast *ast);
int				parse_redirection(t_minishell *shell, t_ast *cmd_node,
					t_token *initial_token);
void			append_redirection(t_ast *cmd_node, t_redirection *redir);
t_node_type		get_redirection_type(t_token *token);
int				parse_command_args(t_ast *cmd_node, t_minishell *shell);

/* Executor Functions */
int				execute_command(t_ast *ast, t_minishell *shell, int in_pipe);
void			execute_pipe(t_ast *ast, t_minishell *shell);
void			execute_simple_command(t_ast *ast, t_minishell *shell,
					int in_pipe);
void			execute_simple_command_with_args(char **argv,
					t_minishell *shell, int in_pipe);
char			**build_argv(t_ast *ast);
void			free_argv(char **argv);
int				setup_redirections(t_ast *ast, int *in_fd, int *out_fd,
					t_minishell *shell);
void			restore_stdio(int saved_stdin, int saved_stdout);
bool			is_builtin(char *command);
void			execute_builtin(char **argv, t_minishell *shell);
void			handle_redirect_error(char *filename, t_minishell *shell);
int				is_valid_identifier(char *str);
void			execute_child_process(char **argv, t_minishell *shell);
int				handle_empty_ast(t_ast *ast, t_minishell *shell, int in_pipe);
int				save_stdio(int *saved_stdin, int *saved_stdout,
					t_minishell *shell, int in_pipe);
int				handle_redirections(t_ast *ast, t_io_state *io,
					t_minishell *shell, int in_pipe);
int				get_command_status(char *cmd);
void			handle_error(char *cmd, char *error_msg, int exit_code,
					t_minishell *shell);
int				redirect_input(int *fd, int std_fd, t_minishell *shell,
					int saved_stdin);
int				redirect_output(int *fd, int std_fd, t_minishell *shell,
					int saved_stdout);

/* Builtin Functions */
void			builtin_cd(char **argv, t_minishell *shell);
void			builtin_echo(char **argv, t_minishell *shell);
void			builtin_pwd(t_minishell *shell);
void			builtin_exit(char **argv, t_minishell *shell);
void			builtin_export(char **argv, t_minishell *shell);
void			builtin_unset(char **argv, t_minishell *shell);

/* Utility Functions */
void			free_env_list(t_env *env_list);
void			free_token(t_token *token);
char			*find_path(t_minishell *shell, char *command);
void			free_paths(char **paths);
void			custom_error(char *message, int error_code);
char			*ft_strjoin_free(char *s1, const char *s2);

/* Environment Functions */
void			init_env(t_env **env_list, char **envp);
t_env			*new_env_node(char *key, char *value);
int				add_back_env(t_env **env_list, t_env *new_env_node);
char			*get_env(t_env *env_list, const char *key);
void			update_env(t_env *env_list, char *key, char *value);
void			remove_env(t_env *env_list, char *key);
void			print_env(t_env *env_list);
void			builtin_env(t_minishell *shell);

#endif