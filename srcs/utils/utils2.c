#include "../../include/minishell.h"

char	*find_path(t_minishell *shell, char *command)
{
	char	*path_command;
	int		i;

	if (!command || !*command)
		return (NULL);
	if (command[0] == '/' || ft_strncmp(command, "./", 2) == 0)
		return (ft_strdup(command));
	i = 0;
	while (shell->paths && shell->paths[i])
	{
		path_command = ft_strjoin(shell->paths[i], "/");
		path_command = ft_strjoin_free(path_command, command);
		if (access(path_command, F_OK) == 0)
			return (path_command);
		free(path_command);
		i++;
	}
	return (NULL);
}

void	free_paths(char **paths)
{
	int	i;

	if (!paths)
		return ;
	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

char	*ft_strjoin_free(char *s1, const char *s2)
{
	char	*result;

	result = ft_strjoin(s1, s2);
	free(s1);
	return (result);
}
