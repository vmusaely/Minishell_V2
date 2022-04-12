#include "minishell.h"

void	*ft_realloc(void *ptr, size_t size)
{
	void	*new_ptr;

	if (!ptr)
		return (malloc(size + 1));
	if (!size)
		return (ptr);
	new_ptr = malloc(size + 1);
	ft_memcpy(new_ptr, ptr, size);
	free(ptr);
	return (new_ptr);
}
