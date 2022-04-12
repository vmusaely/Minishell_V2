#include "minishell.h"

t_list	*expander_from_env(t_list *list, char *env)
{
	char	**split;
	size_t	i;

	split = ft_split(env, ' ');
	i = 0;
	while (split[i] != NULL)
	{
		list = list_push(list, list_create(split[i]));
		free(split[i++]);
	}
	free(split);
	return (list);
}

char	*expander_merge(t_string *temp, t_node *node, bool no_env)
{
	t_node	*merge;
	char	*temp_value;

	if (!node)
		return (string_freeze(temp));
	merge = node->merged;
	while (merge)
	{
		temp_value = expander_simple_word(merge, no_env);
		if (temp_value)
		{
			string_push(temp, temp_value);
			free(temp_value);
		}
		merge = merge->merged;
	}
	return (string_freeze(temp));
}
