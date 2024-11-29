// srcs/handle_input.c

#include "../include/minishell.h"

static void		read_and_add_history(t_minishell *shell);
static t_ast	*parse_input(t_minishell *shell);
static void		execute_parsed_ast(t_ast *ast, t_minishell *shell);
static void		cleanup_input(t_minishell *shell);

void	handle_input(t_minishell *shell)
{
	t_ast	*ast;

	read_and_add_history(shell);
	ast = parse_input(shell);
	if (ast)
	{
		execute_parsed_ast(ast, shell);
		free_ast(ast);
	}
	cleanup_input(shell);
}

static void	read_and_add_history(t_minishell *shell)
{
	shell->input = readline(C_PINK "minishell> " C_DEF);
	if (!shell->input)
	{
		ft_putstr_fd("exit\n", 1);
		clear_minishell(shell);
		exit(EXIT_SUCCESS);
	}
	if (*(shell->input))
		add_history(shell->input);
}

static t_ast	*parse_input(t_minishell *shell)
{
	shell->lexer = init_lexer(shell->input);
	if (!shell->lexer)
	{
		perror("Failed to initialize lexer");
		free(shell->input);
		return (NULL);
	}
	return (ft_parser(shell));
}

static void	execute_parsed_ast(t_ast *ast, t_minishell *shell)
{
	execute_command(ast, shell, 0);
}

static void	cleanup_input(t_minishell *shell)
{
	if (shell->input)
	{
		free(shell->input);
		shell->input = NULL;
	}
	if (shell->lexer)
	{
		if (shell->lexer->saved_token)
			free_token(shell->lexer->saved_token);
		free(shell->lexer);
		shell->lexer = NULL;
	}
}
