#include "../../include/minishell.h"

t_token	*create_token(t_token_type type, char *value)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = value;
	return (token);
}

void	free_token(t_token *token)
{
	if (token->value)
		free(token->value);
	free(token);
}
