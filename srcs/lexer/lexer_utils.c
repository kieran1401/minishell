#include "../../include/minishell.h"

void	advance(t_lexer *lexer)
{
	lexer->pos++;
	if (lexer->pos < ft_strlen(lexer->input))
		lexer->current_char = lexer->input[lexer->pos];
	else
		lexer->current_char = '\0';
}

void	skip_whitespace(t_lexer *lexer)
{
	while (lexer->current_char != '\0' && ft_isspace(lexer->current_char))
		advance(lexer);
}

void	save_token(t_lexer *lexer, t_token *token)
{
	lexer->saved_token = token;
}

t_token	*get_saved_token(t_lexer *lexer)
{
	t_token	*token;

	token = lexer->saved_token;
	lexer->saved_token = NULL;
	return (token);
}
