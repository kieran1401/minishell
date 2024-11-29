#include "../../include/minishell.h"
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>

static int	create_pipe(int pipefd[2])
{
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (0);
	}
	return (1);
}

static void	execute_pipe_child1(t_ast *ast, t_minishell *shell, int pipefd[2])
{
	close(pipefd[0]);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
	if (!execute_command(ast->left, shell, 1))
		exit(shell->last_exit_status);
	exit(shell->last_exit_status);
}

static void	execute_pipe_child2(t_ast *ast, t_minishell *shell, int pipefd[2])
{
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	if (!execute_command(ast->right, shell, 1))
		exit(shell->last_exit_status);
	exit(shell->last_exit_status);
}

static void	close_pipe_and_wait(int pipefd[2], pid_t pid1, pid_t pid2,
		t_minishell *shell)
{
	int	status1;
	int	status2;

	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid1, &status1, 0);
	waitpid(pid2, &status2, 0);
	if (WIFEXITED(status2))
		shell->last_exit_status = WEXITSTATUS(status2);
	else
		shell->last_exit_status = 1;
}

void	execute_pipe(t_ast *ast, t_minishell *shell)
{
	int		pipefd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (!create_pipe(pipefd))
		return ;
	pid1 = fork();
	if (pid1 == 0)
		execute_pipe_child1(ast, shell, pipefd);
	pid2 = fork();
	if (pid2 == 0)
		execute_pipe_child2(ast, shell, pipefd);
	close_pipe_and_wait(pipefd, pid1, pid2, shell);
}
