#include "../include/minishell.h"

t_minishell	*initialize_minishell(char **envp)
{
	t_minishell	*shell;

	shell = (t_minishell *)malloc(sizeof(t_minishell));
	if (!shell)
		return (NULL);
	shell->input = NULL;
	shell->envp = envp;
	shell->paths = NULL;
	shell->env_lst = NULL;
	shell->lexer = NULL;
	init_env(&shell->env_lst, envp);
	shell->paths = ft_split(getenv("PATH"), ':');
	return (shell);
}

void	clear_minishell(t_minishell *shell)
{
	if (!shell)
		return ;
	if (shell->input)
		free(shell->input);
	if (shell->lexer)
	{
		if (shell->lexer->saved_token)
			free_token(shell->lexer->saved_token);
		free(shell->lexer);
	}
	if (shell->env_lst)
		free_env_list(shell->env_lst);
	if (shell->paths)
		free_paths(shell->paths);
	free(shell);
}
