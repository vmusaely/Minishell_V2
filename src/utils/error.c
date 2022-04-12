#include "minishell.h"

void	error_print(char *msg1, char *msg2, char *msg3, char *msg4)
{
	if (msg1)
		ft_putstr_fd(msg1, STDERR_FILENO);
	if (msg2)
	{
		if (msg1)
			ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(msg2, STDERR_FILENO);
	}
	if (msg3)
	{
		if (msg1 || msg2)
			ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(msg3, STDERR_FILENO);
	}
	if (msg4)
	{
		if (msg1 || msg2 || msg3)
			ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(msg4, STDERR_FILENO);
	}
	ft_putchar_fd('\n', STDERR_FILENO);
}

void	error_print_code(char *msg1, char *msg2, char *msg3)
{
	error_print(msg1, msg2, msg3, strerror(errno));
}
