#include "../../include/minishell.h"

static int	validate_unset_arg(char *arg)
{
	return (is_valid_identifier(arg));
}

void	builtin_unset(char **argv, t_minishell *shell)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (validate_unset_arg(argv[i]))
			remove_env(shell->env_lst, argv[i]);
		i++;
	}
	shell->last_exit_status = 0;
}
