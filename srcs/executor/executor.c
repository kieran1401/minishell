#include "../../include/minishell.h"
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>

static t_ast	*find_command_node(t_ast *ast)
{
	while (ast
		&& (ast->type == NODE_REDIRECT_IN
			|| ast->type == NODE_REDIRECT_OUT
			|| ast->type == NODE_REDIRECT_APPEND))
	{
		ast = ast->left;
	}
	return (ast);
}

static void	execute_command_node(t_ast *cmd_node,
		t_minishell *shell, int in_pipe)
{
	if (cmd_node)
	{
		if (cmd_node->type == NODE_PIPE)
			execute_pipe(cmd_node, shell);
		else
			execute_simple_command(cmd_node, shell, in_pipe);
	}
	else
	{
		shell->last_exit_status = 127;
		if (in_pipe)
			exit(shell->last_exit_status);
	}
}

int	execute_command(t_ast *ast, t_minishell *shell, int in_pipe)
{
	t_io_state		io;
	t_ast			*cmd_node;

	if (!handle_empty_ast(ast, shell, in_pipe))
		return (0);
	io.in_fd = STDIN_FILENO;
	io.out_fd = STDOUT_FILENO;
	if (!save_stdio(&io.saved_stdin, &io.saved_stdout, shell, in_pipe))
		return (0);
	if (!handle_redirections(ast, &io, shell, in_pipe))
		return (0);
	if (!redirect_input(&io.in_fd, STDIN_FILENO, shell, io.saved_stdin))
		return (0);
	if (!redirect_output(&io.out_fd, STDOUT_FILENO, shell, io.saved_stdout))
		return (0);
	cmd_node = find_command_node(ast);
	execute_command_node(cmd_node, shell, in_pipe);
	restore_stdio(io.saved_stdin, io.saved_stdout);
	if (in_pipe)
		exit(shell->last_exit_status);
	return (1);
}
