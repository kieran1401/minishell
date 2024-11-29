#include "../../include/minishell.h"
#include <errno.h>
#include <string.h>

static char	*get_redirect_error_msg(int err_code)
{
	if (err_code == ENOENT)
		return ("No such file or directory");
	else if (err_code == EACCES)
		return ("Permission denied");
	else if (err_code == EISDIR)
		return ("Is a directory");
	return (strerror(err_code));
}

static int	get_redirect_exit_code(int err_code)
{
	if (err_code == EISDIR)
		return (126);
	return (1);
}

void	handle_redirect_error(char *filename, t_minishell *shell)
{
	char	*error_msg;
	int		exit_code;

	exit_code = get_redirect_exit_code(errno);
	error_msg = get_redirect_error_msg(errno);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(filename, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(error_msg, 2);
	ft_putstr_fd("\n", 2);
	shell->last_exit_status = exit_code;
}
