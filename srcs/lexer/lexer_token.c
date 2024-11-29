#include "../../include/minishell.h"

t_token	*handle_word(t_lexer *lexer, t_minishell *shell)
{
	char	buffer[BUFFER_SIZE];
	int		pos;

	pos = 0;
	while (lexer->current_char != '\0' && !ft_isspace(lexer->current_char)
		&& lexer->current_char != '|' && lexer->current_char != '<'
		&& lexer->current_char != '>')
	{
		pos = handle_word_dispatcher(lexer, buffer, pos, shell);
		if (pos == -1)
		{
			printf("minishell: Error: Unmatched or unclosed quote\n");
			shell->last_exit_status = 1;
			return (NULL);
		}
	}
	buffer[pos] = '\0';
	return (create_token(TOKEN_WORD, ft_strdup(buffer)));
}

t_token	*handle_less_than(t_lexer *lexer)
{
	advance(lexer);
	if (lexer->current_char == '<')
	{
		advance(lexer);
		return (create_token(TOKEN_REDIRECT_HEREDOC, ft_strdup("<<")));
	}
	return (create_token(TOKEN_REDIRECT_IN, ft_strdup("<")));
}

t_token	*handle_greater_than(t_lexer *lexer)
{
	advance(lexer);
	if (lexer->current_char == '>')
	{
		advance(lexer);
		return (create_token(TOKEN_REDIRECT_APPEND, ft_strdup(">>")));
	}
	return (create_token(TOKEN_REDIRECT_OUT, ft_strdup(">")));
}
