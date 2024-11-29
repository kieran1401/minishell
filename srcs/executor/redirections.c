#include "../../include/minishell.h"
#include <errno.h>
#include <sys/stat.h>

int	setup_input_redirection(char *filename, int *in_fd, t_minishell *shell)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		handle_redirect_error(filename, shell);
		return (0);
	}
	if (*in_fd != STDIN_FILENO)
		close(*in_fd);
	*in_fd = fd;
	return (1);
}

int	setup_output_redirection(t_node_type type, char *filename,
		int *out_fd, t_minishell *shell)
{
	int	fd;

	if (type == NODE_REDIRECT_OUT)
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		handle_redirect_error(filename, shell);
		return (0);
	}
	if (*out_fd != STDOUT_FILENO)
		close(*out_fd);
	*out_fd = fd;
	return (1);
}

int	setup_redirections(t_ast *ast, int *in_fd, int *out_fd, t_minishell *shell)
{
	t_redirection	*redir;
	int				result;

	redir = ast->redirections;
	while (redir)
	{
		if (redir->type == NODE_REDIRECT_IN)
			result = setup_input_redirection(redir->filename, in_fd, shell);
		else
			result = setup_output_redirection(redir->type, redir->filename,
					out_fd, shell);
		if (!result)
			return (0);
		redir = redir->next;
	}
	return (1);
}

void	restore_stdio(int saved_stdin, int saved_stdout)
{
	if (saved_stdin != -1)
	{
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdin);
	}
	if (saved_stdout != -1)
	{
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);
	}
}

int	handle_redirections(t_ast *ast, t_io_state *io,
		t_minishell *shell, int in_pipe)
{
	if (!setup_redirections(ast, &io->in_fd, &io->out_fd, shell))
	{
		restore_stdio(io->saved_stdin, io->saved_stdout);
		shell->last_exit_status = 1;
		if (in_pipe)
			exit(1);
		return (0);
	}
	return (1);
}
