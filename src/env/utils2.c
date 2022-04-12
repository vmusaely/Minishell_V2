#include "minishell.h"

static bool	env_split(char *value, char **a, char **b)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(value);
	if (!value)
		return (false);
	while (value[i] != '=' && value[i] != '\0')
		i++;
	if (value[i] == '\0')
		return (false);
	*a = ft_substr(value, 0, i++);
	*b = ft_substr(value, i, len - i);
	return (true);
}

int	env_from_string(char *string)
{
	char	*a;
	char	*b;
	bool	code;

	code = 0;
	b = NULL;
	a = NULL;
	if (ft_strchr(string, '=') == NULL)
		a = ft_strdup(string);
	else
		env_split(string, &a, &b);
	if (ft_strchr(a, ' '))
	{
		printf("export: '%s' is not a valid identifier\n", a);
		code = 1;
	}
	else
		env_set(a, b);
	if (a)
		free(a);
	if (b)
		free(b);
	return (code);
}

char	*env_value_or_null(char *value)
{
	if (value == NULL)
		return (NULL);
	return (ft_strdup(value));
}
