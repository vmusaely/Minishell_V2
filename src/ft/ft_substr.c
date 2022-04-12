#include "minishell.h"

// char	*ft_substr(char const *s, unsigned int start, size_t len)
// {
// 	char	*ptr;

// 	if (!s)
// 		return (NULL);
// 	ptr = ft_calloc(len + 1, sizeof(char));
// 	if (!ptr)
// 		return (NULL);
// 	if (start >= ft_strlen(s))
// 		return (ptr);
// 	ft_memcpy(ptr, s + start, len);
// 	if (ptr[len] != '\0')
// 		ptr[len] = '\0';
// 	return (ptr);
// }

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	index;

	if (!s)
		return (NULL);
	if ((size_t)start > ft_strlen(s))
		return (ft_strdup(""));
	substr = malloc(len + 1);
	if (!substr)
		return (NULL);
	index = 0;
	while (index < len)
	{
		substr[index] = *(s + start + index);
		index++;
	}
	substr[index] = '\0';
	return (substr);
}
