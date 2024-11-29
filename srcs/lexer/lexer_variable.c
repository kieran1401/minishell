#include "../../include/minishell.h"

/* Append Variable Value ($VAR) */
int	append_variable(t_lexer *lexer, char *buffer, int pos, t_minishell *shell)
{
	char	*var_name;
	char	*env_value;
	int		i;

	var_name = extract_variable_name(lexer);
	if (var_name[0] == '\0')
	{
		buffer[pos++] = '$';
		free(var_name);
		return (pos);
	}
	env_value = get_env(shell->env_lst, var_name);
	free(var_name);
	if (env_value)
	{
		i = 0;
		while (env_value[i])
			buffer[pos++] = env_value[i++];
		free(env_value);
	}
	return (pos);
}

char	*extract_variable_name(t_lexer *lexer)
{
	char	buffer[BUFFER_SIZE];
	int		pos;

	pos = 0;
	advance(lexer);
	while (lexer->current_char != '\0' && (ft_isalnum(lexer->current_char)
			|| lexer->current_char == '_'))
	{
		buffer[pos++] = lexer->current_char;
		advance(lexer);
	}
	buffer[pos] = '\0';
	return (ft_strdup(buffer));
}
