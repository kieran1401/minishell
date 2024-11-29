#include "../../include/minishell.h"
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>

int	get_command_status(char *cmd)
{
	struct stat	path_stat;

	if (!cmd)
		return (127);
	if (stat(cmd, &path_stat) == 0)
	{
		if (S_ISDIR(path_stat.st_mode))
			return (126);
		if (!(path_stat.st_mode & S_IXUSR))
			return (126);
	}
	return (0);
}

void	execute_simple_command_with_args(char **argv,
		t_minishell *shell, int in_pipe)
{
	t_ast	temp_ast;

	temp_ast.type = NODE_COMMAND;
	temp_ast.value = argv[0];
	temp_ast.left = NULL;
	temp_ast.right = NULL;
	execute_simple_command(&temp_ast, shell, in_pipe);
}

void	handle_error(char *cmd, char *error_msg,
		int exit_code, t_minishell *shell)
{
	if (cmd)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
	}
	if (error_msg)
	{
		ft_putstr_fd(error_msg, 2);
		ft_putstr_fd("\n", 2);
	}
	shell->last_exit_status = exit_code;
}
