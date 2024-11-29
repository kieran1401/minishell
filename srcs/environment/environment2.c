#include "../../include/minishell.h"

void	update_env(t_env *env_list, char *key, char *value)
{
	t_env	*env;
	t_env	*new_node;

	env = env_list;
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
		{
			free(env->value);
			env->value = ft_strdup(value);
			return ;
		}
		env = env->next;
	}
	new_node = new_env_node(key, value);
	if (new_node)
		add_back_env(&env_list, new_node);
}

void	remove_env(t_env *env_list, char *key)
{
	t_env	*temp;
	t_env	*prev;

	temp = env_list;
	prev = NULL;
	while (temp)
	{
		if (ft_strcmp(temp->key, key) == 0)
		{
			if (prev)
				prev->next = temp->next;
			else
				env_list = temp->next;
			free(temp->key);
			free(temp->value);
			free(temp);
			return ;
		}
		prev = temp;
		temp = temp->next;
	}
}

void	print_env(t_env *env_list)
{
	while (env_list)
	{
		printf("%s=%s\n", env_list->key, env_list->value);
		env_list = env_list->next;
	}
}
