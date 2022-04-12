#include "minishell.h"

// char	*ft_strchr(const char *str, int c)
// {
// 	while (*str)
// 	{
// 		if (*str == c)
// 			return ((char *)str);
// 		++str;
// 	}
// 	if (c == '\0')
// 		return ((char *)str);
// 	return (NULL);
// }

char			*ft_strchr(const char *s, int c)
{
	size_t	i;
	size_t	len;

	len = 0;
	i = 0;
	while (s[len])
	{
		len++;
	}
	while (i <= len)
	{
		if (s[i] == c)
		{
			return (char*)(s + i);
		}
		i++;
	}
	return (NULL);
}
