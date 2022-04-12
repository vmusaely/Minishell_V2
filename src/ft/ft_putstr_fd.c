#include "minishell.h"

void	ft_putstr_fd(const char *s, int fd)
{
	while (s && *s)
		write(fd, s++, 1);
}
