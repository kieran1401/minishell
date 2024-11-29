#include "../../include/minishell.h"
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>

static void	handle_empty_argv(char **argv, t_minishell *shell, int in_pipe)
{
	if (!argv || !argv[0] || !argv[0][0])
	{
		if (argv && argv[1])
			execute_simple_command_with_args(&argv[1], shell, in_pipe);
		free_argv(argv);
	}
}

static void	handle_builtin_execution(char **argv,
		t_minishell *shell, int in_pipe)
{
	if (is_builtin(argv[0]) && !in_pipe)
	{
		execute_builtin(argv, shell);
	}
}

static void	handle_fork_execution(char **argv, t_minishell *shell)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		execute_child_process(argv, shell);
	}
	else if (pid < 0)
	{
		perror("fork");
		shell->last_exit_status = 1;
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			shell->last_exit_status = WEXITSTATUS(status);
		else
			shell->last_exit_status = 1;
	}
}

static void	execute_builtin_or_external(char **argv,
		t_minishell *shell, int in_pipe)
{
	if (is_builtin(argv[0]) && !in_pipe)
	{
		handle_builtin_execution(argv, shell, in_pipe);
		return ;
	}
	handle_fork_execution(argv, shell);
}

void	execute_simple_command(t_ast *ast, t_minishell *shell, int in_pipe)
{
	char	**argv;

	argv = build_argv(ast);
	handle_empty_argv(argv, shell, in_pipe);
	if (!argv || !argv[0] || !argv[0][0])
		return ;
	execute_builtin_or_external(argv, shell, in_pipe);
	free_argv(argv);
}
