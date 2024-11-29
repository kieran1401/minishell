#include "../../include/minishell.h"

t_lexer	*init_lexer(char *input)
{
	t_lexer	*lexer;

	lexer = (t_lexer *)malloc(sizeof(t_lexer));
	if (!lexer)
		return (NULL);
	lexer->input = input;
	lexer->pos = 0;
	lexer->current_char = input[0];
	lexer->saved_token = NULL;
	return (lexer);
}

static t_token	*handle_special_chars(t_lexer *lexer)
{
	if (lexer->current_char == '|')
	{
		advance(lexer);
		return (create_token(TOKEN_PIPE, ft_strdup("|")));
	}
	if (lexer->current_char == '<')
		return (handle_less_than(lexer));
	if (lexer->current_char == '>')
		return (handle_greater_than(lexer));
	return (NULL);
}

t_token	*get_next_token(t_lexer *lexer, t_minishell *shell)
{
	t_token	*token;
	t_token	*special_token;

	if (lexer->saved_token)
		return (get_saved_token(lexer));
	while (lexer->current_char != '\0')
	{
		if (ft_isspace(lexer->current_char))
		{
			skip_whitespace(lexer);
			continue ;
		}
		special_token = handle_special_chars(lexer);
		if (special_token)
			return (special_token);
		token = handle_word(lexer, shell);
		return (token);
	}
	return (create_token(TOKEN_EOF, NULL));
}
