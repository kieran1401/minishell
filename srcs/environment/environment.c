#include "../../include/minishell.h"

void	init_env(t_env **env_list, char **envp)
{
	int		i;
	char	*key;
	char	*value;
	char	*ptr;

	*env_list = NULL;
	i = 0;
	while (envp[i] != NULL)
	{
		ptr = ft_strchr(envp[i], '=');
		if (ptr)
		{
			key = ft_substr(envp[i], 0, ptr - envp[i]);
			value = ft_strdup(ptr + 1);
			add_back_env(env_list, new_env_node(key, value));
			free(key);
			free(value);
		}
		i++;
	}
}

t_env	*new_env_node(char *key, char *value)
{
	t_env	*new_node;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->key = ft_strdup(key);
	new_node->value = ft_strdup(value);
	new_node->next = NULL;
	return (new_node);
}

int	add_back_env(t_env **env_list, t_env *new_env_node)
{
	t_env	*temp;

	if (!new_env_node)
		return (1);
	if (*env_list == NULL)
	{
		*env_list = new_env_node;
		return (0);
	}
	temp = *env_list;
	while (temp->next)
		temp = temp->next;
	temp->next = new_env_node;
	return (0);
}

char	*get_env(t_env *env_list, const char *key)
{
	t_env	*env;

	env = env_list;
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (ft_strdup(env->value));
		env = env->next;
	}
	return (NULL);
}
