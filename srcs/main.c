#include "../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_minishell	*shell;

	(void)argc;
	(void)argv;
	shell = initialize_minishell(envp);
	if (!shell)
	{
		perror("Failed to initialize minishell");
		exit(EXIT_FAILURE);
	}
	setup_signal_handlers();
	while (true)
		handle_input(shell);
	clear_minishell(shell);
	return (0);
}
