#include "minishell.h"

void	*ft_memcpy(void *dest, const void *src, size_t num)
{
	unsigned char		*d;
	const unsigned char	*s;

	if (!dest && !src)
		return (0);
	d = dest;
	s = src;
	while (num-- > 0 && *s)
		*d++ = *s++;
	return (dest);
}
