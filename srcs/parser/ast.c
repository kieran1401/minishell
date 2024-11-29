#include "../../include/minishell.h"

t_ast	*create_ast_node(t_node_type type, char *value)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = type;
	node->value = value;
	node->redirections = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

void	free_ast(t_ast *ast)
{
	t_redirection	*redir;
	t_redirection	*next;

	if (!ast)
		return ;
	if (ast->value)
		free(ast->value);
	if (ast->left)
		free_ast(ast->left);
	if (ast->right)
		free_ast(ast->right);
	redir = ast->redirections;
	while (redir)
	{
		next = redir->next;
		if (redir->filename)
			free(redir->filename);
		free(redir);
		redir = next;
	}
	free(ast);
}
