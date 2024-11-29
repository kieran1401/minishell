#include "../../include/minishell.h"

int	parse_command_args(t_ast *cmd_node, t_minishell *shell);

t_ast	*parse_command(t_minishell *shell)
{
	t_ast	*cmd_node;
	t_token	*token;

	token = get_next_token(shell->lexer, shell);
	if (!token || token->type != TOKEN_WORD)
	{
		if (token)
			free_token(token);
		return (NULL);
	}
	cmd_node = create_ast_node(NODE_COMMAND, ft_strdup(token->value));
	free_token(token);
	if (!parse_command_args(cmd_node, shell))
	{
		free_ast(cmd_node);
		return (NULL);
	}
	return (cmd_node);
}

int	process_token(t_ast **current_arg, t_ast *cmd_node,
		t_token *token, t_minishell *shell)
{
	if (is_redirection(token->type))
	{
		if (!parse_redirection(shell, cmd_node, token))
			return (0);
	}
	else if (token->type == TOKEN_WORD)
	{
		(*current_arg)->right = create_ast_node(NODE_ARGS,
				ft_strdup(token->value));
		*current_arg = (*current_arg)->right;
		free_token(token);
	}
	else
	{
		save_token(shell->lexer, token);
		return (0);
	}
	return (1);
}

int	parse_command_args(t_ast *cmd_node, t_minishell *shell)
{
	t_ast	*current_arg;
	t_token	*token;

	current_arg = cmd_node;
	while (1)
	{
		token = get_next_token(shell->lexer, shell);
		if (token == NULL)
			break ;
		if (!process_token(&current_arg, cmd_node, token, shell))
			break ;
	}
	return (1);
}
