#include "../../include/minishell.h"

int	is_valid_identifier(char *str)
{
	int	i;

	if (!str || !*str || (!isalpha(str[0]) && str[0] != '_'))
		return (0);
	i = 1;
	while (str[i])
	{
		if (!isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
