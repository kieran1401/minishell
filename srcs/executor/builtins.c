#include "../../include/minishell.h"

bool	is_builtin(char *command)
{
	if (ft_strcmp(command, "cd") == 0)
		return (true);
	if (ft_strcmp(command, "echo") == 0)
		return (true);
	if (ft_strcmp(command, "pwd") == 0)
		return (true);
	if (ft_strcmp(command, "env") == 0)
		return (true);
	if (ft_strcmp(command, "exit") == 0)
		return (true);
	if (ft_strcmp(command, "export") == 0)
		return (true);
	if (ft_strcmp(command, "unset") == 0)
		return (true);
	return (false);
}

void	execute_builtin(char **argv, t_minishell *shell)
{
	if (ft_strcmp(argv[0], "cd") == 0)
		builtin_cd(argv, shell);
	else if (ft_strcmp(argv[0], "echo") == 0)
		builtin_echo(argv, shell);
	else if (ft_strcmp(argv[0], "pwd") == 0)
		builtin_pwd(shell);
	else if (ft_strcmp(argv[0], "env") == 0)
		builtin_env(shell);
	else if (ft_strcmp(argv[0], "exit") == 0)
		builtin_exit(argv, shell);
	else if (ft_strcmp(argv[0], "export") == 0)
		builtin_export(argv, shell);
	else if (ft_strcmp(argv[0], "unset") == 0)
		builtin_unset(argv, shell);
}

void	builtin_pwd(t_minishell *shell)
{
	char	cwd[BUFFER_SIZE];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		printf("%s\n", cwd);
		shell->last_exit_status = 0;
	}
	else
	{
		perror("pwd");
		shell->last_exit_status = 1;
	}
}

void	builtin_env(t_minishell *shell)
{
	t_env	*env;

	env = shell->env_lst;
	while (env)
	{
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	shell->last_exit_status = 0;
}
