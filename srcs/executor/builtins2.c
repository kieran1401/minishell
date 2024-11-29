#include "../../include/minishell.h"

void	builtin_echo(char **argv, t_minishell *shell)
{
	int		i;
	int		newline;

	(void)shell;
	i = 1;
	newline = 1;
	if (argv[1] && ft_strcmp(argv[1], "-n") == 0)
	{
		newline = 0;
		i++;
	}
	while (argv[i])
	{
		ft_putstr_fd(argv[i], 1);
		if (argv[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (newline)
		ft_putchar_fd('\n', 1);
	shell->last_exit_status = 0;
}

static void	handle_exit_error(char *arg, t_minishell *shell)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	clear_minishell(shell);
	exit(2);
}

void	builtin_exit(char **argv, t_minishell *shell)
{
	int	exit_status;

	ft_putstr_fd("exit\n", 1);
	if (!argv[1])
	{
		clear_minishell(shell);
		exit(0);
	}
	if (argv[1] && !ft_isnumber(argv[1]))
		handle_exit_error(argv[1], shell);
	if (argv[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		shell->last_exit_status = 1;
		return ;
	}
	exit_status = ft_atoi(argv[1]) % 256;
	if (exit_status < 0)
		exit_status += 256;
	clear_minishell(shell);
	exit(exit_status);
}
