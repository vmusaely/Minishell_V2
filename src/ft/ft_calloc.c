#include "minishell.h"

void	*ft_calloc(size_t el_num, size_t el_size)
{
	void	*ptr;

	if (el_num == 0 && el_size == 0)
	{
		el_num = 1;
		el_size = 1;
	}
	ptr = malloc(el_num * el_size);
	if (ptr)
		ft_memset(ptr, 0, el_num * el_size);
	return (ptr);
}
