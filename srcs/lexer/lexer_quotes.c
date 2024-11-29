#include "../../include/minishell.h"

int	handle_quotes(t_lexer *lexer, char *buffer, int pos, t_minishell *shell)
{
	char	quote;

	quote = lexer->current_char;
	advance(lexer);
	while (lexer->current_char != '\0' && lexer->current_char != quote)
	{
		if (quote == '"')
			pos = handle_double_quotes(lexer, buffer, pos, shell);
		else
			pos = handle_single_quotes(lexer, buffer, pos);
		if (pos == -1)
			return (-1);
	}
	if (lexer->current_char == quote)
		advance(lexer);
	else
		return (-1);
	return (pos);
}

int	handle_double_quotes(t_lexer *lexer, char *buffer,
		int pos, t_minishell *shell)
{
	if (lexer->current_char == '$')
		pos = handle_dollar_in_quotes(lexer, buffer, pos, shell);
	else
		pos = append_char_to_buffer(lexer, buffer, pos);
	return (pos);
}

int	handle_single_quotes(t_lexer *lexer, char *buffer, int pos)
{
	return (append_char_to_buffer(lexer, buffer, pos));
}

int	append_char_to_buffer(t_lexer *lexer, char *buffer, int pos)
{
	buffer[pos++] = lexer->current_char;
	advance(lexer);
	return (pos);
}

int	handle_dollar_in_quotes(t_lexer *lexer, char *buffer,
		int pos, t_minishell *shell)
{
	if (lexer->input[lexer->pos + 1] == '?')
		pos = append_exit_status(lexer, buffer, pos, shell);
	else
		pos = append_variable(lexer, buffer, pos, shell);
	return (pos);
}
