#include "../../include/minishell.h"

static void	handle_invalid_export(char *arg)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

static char	*get_key(char *arg)
{
	char	*equal_sign;

	equal_sign = ft_strchr(arg, '=');
	if (equal_sign)
		return (ft_substr(arg, 0, equal_sign - arg));
	return (ft_strdup(arg));
}

static char	*get_value(char *equal_sign)
{
	if (!equal_sign)
		return (NULL);
	return (ft_strdup(equal_sign + 1));
}

static int	process_export_argument(char *arg, t_minishell *shell)
{
	char	*key;
	char	*value;
	char	*equal_sign;

	value = NULL;
	equal_sign = ft_strchr(arg, '=');
	key = get_key(arg);
	if (!is_valid_identifier(key))
	{
		handle_invalid_export(arg);
		free(key);
		return (1);
	}
	if (equal_sign)
	{
		value = get_value(equal_sign);
		update_env(shell->env_lst, key, value);
		free(value);
	}
	free(key);
	return (0);
}

void	builtin_export(char **argv, t_minishell *shell)
{
	int	i;

	i = 1;
	if (!argv[1])
	{
		print_env(shell->env_lst);
		shell->last_exit_status = 0;
		return ;
	}
	shell->last_exit_status = 0;
	while (argv[i])
	{
		if (process_export_argument(argv[i], shell))
			shell->last_exit_status = 1;
		i++;
	}
}
