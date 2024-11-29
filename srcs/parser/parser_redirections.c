#include "../../include/minishell.h"

int	parse_redirection(t_minishell *shell, t_ast *cmd_node,
		t_token *initial_token)
{
	t_redirection	*redir;

	redir = create_redirection(shell, initial_token);
	if (!redir)
		return (0);
	append_redirection(cmd_node, redir);
	return (1);
}

t_redirection	*create_redirection(t_minishell *shell, t_token *initial_token)
{
	t_node_type		type;
	t_token			*token;
	t_redirection	*redir;

	type = get_redirection_type(initial_token);
	free_token(initial_token);
	if (type == NODE_INVALID)
		return (NULL);
	token = get_next_token(shell->lexer, shell);
	if (!token || token->type != TOKEN_WORD)
	{
		if (token)
			free_token(token);
		return (NULL);
	}
	redir = malloc(sizeof(t_redirection));
	if (!redir)
		return (NULL);
	redir->type = type;
	redir->filename = ft_strdup(token->value);
	redir->next = NULL;
	free_token(token);
	return (redir);
}

void	append_redirection(t_ast *cmd_node, t_redirection *redir)
{
	t_redirection	*last;

	if (!cmd_node->redirections)
		cmd_node->redirections = redir;
	else
	{
		last = cmd_node->redirections;
		while (last->next)
			last = last->next;
		last->next = redir;
	}
}

t_node_type	get_redirection_type(t_token *token)
{
	if (token->type == TOKEN_REDIRECT_IN)
		return (NODE_REDIRECT_IN);
	if (token->type == TOKEN_REDIRECT_OUT)
		return (NODE_REDIRECT_OUT);
	if (token->type == TOKEN_REDIRECT_APPEND)
		return (NODE_REDIRECT_APPEND);
	return (NODE_INVALID);
}

int	is_redirection(t_token_type type)
{
	return (
		(type == TOKEN_REDIRECT_IN)
		|| (type == TOKEN_REDIRECT_OUT)
		|| (type == TOKEN_REDIRECT_APPEND)
		|| (type == TOKEN_REDIRECT_HEREDOC)
	);
}
