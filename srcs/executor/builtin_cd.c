#include "../../include/minishell.h"

static char	*get_cd_path(char **argv, t_minishell *shell);
static void	handle_cd_error(t_minishell *shell, char *path);
static void	update_directory_env(t_minishell *shell, char *current_dir);
static int	validate_cd_args(char **argv, t_minishell *shell);

static char	*get_cd_path(char **argv, t_minishell *shell)
{
	if (!argv[1] || ft_strcmp(argv[1], "~") == 0)
		return (get_env(shell->env_lst, "HOME"));
	return (ft_strdup(argv[1]));
}

static void	handle_cd_error(t_minishell *shell, char *path)
{
	perror("cd");
	shell->last_exit_status = 1;
	free(path);
}

static void	update_directory_env(t_minishell *shell, char *current_dir)
{
	char	new_dir[1024];

	update_env(shell->env_lst, "OLDPWD", current_dir);
	if (getcwd(new_dir, sizeof(new_dir)) != NULL)
		update_env(shell->env_lst, "PWD", new_dir);
}

static int	validate_cd_args(char **argv, t_minishell *shell)
{
	if (argv[1] && argv[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		shell->last_exit_status = 1;
		return (0);
	}
	return (1);
}

void	builtin_cd(char **argv, t_minishell *shell)
{
	char	current_dir[1024];
	char	*path;

	if (!validate_cd_args(argv, shell))
		return ;
	if (!getcwd(current_dir, sizeof(current_dir)))
	{
		perror("minishell: cd: getcwd");
		shell->last_exit_status = 1;
		return ;
	}
	path = get_cd_path(argv, shell);
	if (chdir(path) != 0)
	{
		handle_cd_error(shell, path);
		return ;
	}
	shell->last_exit_status = 0;
	update_directory_env(shell, current_dir);
	free(path);
}
