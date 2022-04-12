#include "minishell.h"

// char	*ft_strdup(const char *s)
// {
// 	char	*ptr;
// 	size_t	len;

// 	len = ft_strlen(s) + 1;
// 	ptr = malloc(len);
// 	if (!ptr)
// 		return (NULL);
// 	if (s)
// 	{
// 		ft_memcpy(ptr, s, len);
// 		ptr[len - 1] = '\0';
// 	}
// 	else
// 		*ptr = '\0';
// 	return (ptr);
// }

char					*ft_strdup(const char *s1)
{
	char	*start;
	int		i;
	int		len;

	len = ft_strlen(s1);
	if (!(start = malloc(len + 1)))
		return (0);
	i = 0;
	while (s1[i] != '\0')
	{
		start[i] = s1[i];
		i++;
	}
	start[i] = 0;
	return (start);
}
