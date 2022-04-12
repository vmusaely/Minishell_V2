#include "minishell.h"

void	*ft_memset(void *buffer, int c, size_t size)
{
	char			*cb;
	unsigned int	i;

	cb = buffer;
	i = 0;
	while (i < size)
		cb[i++] = c;
	return (cb);
}
