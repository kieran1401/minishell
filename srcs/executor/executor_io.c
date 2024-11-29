#include "../../include/minishell.h"
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>

int	handle_empty_ast(t_ast *ast, t_minishell *shell, int in_pipe)
{
	if (!ast)
	{
		if (in_pipe)
			exit(shell->last_exit_status);
		return (0);
	}
	return (1);
}

int	save_stdio(int *saved_stdin, int *saved_stdout,
		t_minishell *shell, int in_pipe)
{
	*saved_stdin = dup(STDIN_FILENO);
	*saved_stdout = dup(STDOUT_FILENO);
	if (*saved_stdin == -1 || *saved_stdout == -1)
	{
		perror("dup");
		shell->last_exit_status = 1;
		if (in_pipe)
			exit(shell->last_exit_status);
		return (0);
	}
	return (1);
}

int	redirect_input(int *fd, int std_fd, t_minishell *shell, int saved_stdin)
{
	(void)saved_stdin;
	if (*fd != std_fd)
	{
		if (dup2(*fd, std_fd) == -1)
		{
			perror("dup2");
			shell->last_exit_status = 1;
			close(*fd);
			return (0);
		}
		close(*fd);
	}
	return (1);
}

int	redirect_output(int *fd, int std_fd, t_minishell *shell, int saved_stdout)
{
	(void)saved_stdout;
	if (*fd != std_fd)
	{
		if (dup2(*fd, std_fd) == -1)
		{
			perror("dup2");
			shell->last_exit_status = 1;
			close(*fd);
			return (0);
		}
		close(*fd);
	}
	return (1);
}
