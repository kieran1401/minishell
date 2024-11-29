#include "../../include/minishell.h"

int	handle_word_dispatcher(t_lexer *lexer, char *buffer,
		int pos, t_minishell *shell)
{
	if (lexer->current_char == '\'' || lexer->current_char == '"')
		pos = handle_quotes(lexer, buffer, pos, shell);
	else if (lexer->current_char == '$')
		pos = handle_dollar(lexer, buffer, pos, shell);
	else
	{
		buffer[pos++] = lexer->current_char;
		advance(lexer);
	}
	return (pos);
}

int	handle_dollar(t_lexer *lexer, char *buffer, int pos, t_minishell *shell)
{
	if (lexer->input[lexer->pos + 1] == '?')
		pos = append_exit_status(lexer, buffer, pos, shell);
	else
		pos = append_variable(lexer, buffer, pos, shell);
	return (pos);
}

int	append_exit_status(t_lexer *lexer, char *buffer,
		int pos, t_minishell *shell)
{
	char	*status_str;
	int		i;

	status_str = ft_itoa(shell->last_exit_status);
	if (!status_str)
		return (pos);
	i = 0;
	while (status_str[i])
		buffer[pos++] = status_str[i++];
	free(status_str);
	advance(lexer);
	advance(lexer);
	return (pos);
}
