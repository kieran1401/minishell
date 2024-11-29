#include "../../include/minishell.h"

int	count_args(t_ast *ast)
{
	int		count;
	t_ast	*node;

	count = 0;
	node = ast;
	while (node)
	{
		if (node->type == NODE_COMMAND || node->type == NODE_ARGS)
			count++;
		node = node->right;
	}
	return (count);
}

char	**build_argv(t_ast *ast)
{
	char	**argv;
	int		argc;
	t_ast	*current;

	argc = 0;
	current = ast;
	while (current)
	{
		if (current->type == NODE_COMMAND || current->type == NODE_ARGS)
			argc++;
		current = current->right;
	}
	argv = (char **)malloc(sizeof(char *) * (argc + 1));
	if (!argv)
		return (NULL);
	current = ast;
	argc = 0;
	while (current)
	{
		if (current->type == NODE_COMMAND || current->type == NODE_ARGS)
			argv[argc++] = ft_strdup(current->value);
		current = current->right;
	}
	argv[argc] = NULL;
	return (argv);
}

void	free_argv(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}
