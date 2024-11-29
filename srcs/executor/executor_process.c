#include "../../include/minishell.h"
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>

static void	handle_execve_error(char **argv, int exit_code)
{
	ft_putstr_fd(argv[0], 2);
	if (exit_code == 126)
		ft_putstr_fd(": Is a directory\n", 2);
	free_argv(argv);
	exit(exit_code);
}

static void	execute_command_execve(char *cmd_path, char **argv,
		t_minishell *shell)
{
	execve(cmd_path, argv, shell->envp);
	perror("execve");
	free_argv(argv);
	exit(EXIT_FAILURE);
}

static void	handle_command_not_found(char **argv)
{
	if (argv[0][0] == '/' || argv[0][0] == '.')
		ft_putstr_fd(": No such file or directory\n", 2);
	else
		ft_putstr_fd(": command not found\n", 2);
	free_argv(argv);
	exit(127);
}

void	execute_child_process(char **argv, t_minishell *shell)
{
	char	*cmd_path;
	int		status;

	if (is_builtin(argv[0]))
	{
		execute_builtin(argv, shell);
		free_argv(argv);
		exit(shell->last_exit_status);
	}
	cmd_path = find_path(shell, argv[0]);
	if (cmd_path)
		status = get_command_status(cmd_path);
	else
		status = get_command_status(argv[0]);
	if (status == 126)
		handle_execve_error(argv, 126);
	if (!cmd_path)
		handle_command_not_found(argv);
	execute_command_execve(cmd_path, argv, shell);
}
