#include "../../include/minishell.h"

t_ast	*ft_parser(t_minishell *shell)
{
	return (parse_pipeline(shell));
}

t_ast	*parse_pipeline(t_minishell *shell)
{
	t_ast	*left;
	t_ast	*result;

	left = parse_command(shell);
	if (!left)
		return (NULL);
	result = parse_pipeline_recursive(left, shell);
	return (result);
}

t_ast	*parse_pipeline_recursive(t_ast *left, t_minishell *shell)
{
	t_token	*token;
	t_ast	*pipe_node;

	token = get_next_token(shell->lexer, shell);
	if (!token || token->type != TOKEN_PIPE)
	{
		if (token)
			save_token(shell->lexer, token);
		return (left);
	}
	pipe_node = create_ast_node(NODE_PIPE, ft_strdup("|"));
	pipe_node->left = left;
	free_token(token);
	pipe_node->right = parse_command(shell);
	if (!pipe_node->right)
	{
		free_ast(pipe_node);
		return (NULL);
	}
	return (parse_pipeline_recursive(pipe_node, shell));
}
