/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmusaely <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 15:33:41 by vmusaely          #+#    #+#             */
/*   Updated: 2022/04/15 15:33:47 by vmusaely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**expander_expand(t_node *node)
{
	t_list	*list;
	char	*temp;

	list = NULL;
	while (node)
	{
		temp = expander_node(node, false);
		if (temp)
		{
			if ((node->kind & NODE_VARIABLE) != 0)
				list = expander_from_env(list, temp);
			else
				list = list_push(list, list_create(temp));
		}
		if (temp != NULL)
			free(temp);
		node = node->next;
	}
	return (list_freeze(list));
}

char	*expander_simple_word(t_node *node, bool no_env)
{
	char		*temp;
	t_string	string;

	if (!node)
		return (NULL);
	if ((node->kind & NODE_VARIABLE) != 0)
	{
		if (no_env || !(ft_isalnum(node->value[0]) || node->value[0] == '?'))
		{
			string_init(&string);
			string_push(&string, "$");
			string_push(&string, node->value);
			return (string_freeze(&string));
		}
		temp = env_get(node->value);
		if (!temp)
			return (NULL);
		return (ft_strdup(temp));
	}
	if ((node->kind & NODE_QUOTED) != 0)
		return (expander_quoted(node->in_quote, no_env));
	return (ft_strdup(node->value));
}

char	*expander_word(t_node *node, bool no_env)
{
	t_string	temp;
	char		*temp_value;

	if (!node)
		return (NULL);
	string_init(&temp);
	temp_value = expander_simple_word(node, no_env);
	string_push(&temp, temp_value);
	free(temp_value);
	return (expander_merge(&temp, node, no_env));
}

char	*expander_node(t_node *node, bool no_env)
{
	if (!node)
		return (NULL);
	if ((node->kind & (NODE_WORD | NODE_VARIABLE | NODE_QUOTED)) != 0)
		return (expander_word(node, no_env));
	return (NULL);
}

char	*expander_quoted(t_node *node, bool no_env)
{
	t_string	string;
	char		*temp;

	string_init(&string);
	string_push(&string, "");
	while (node)
	{
		temp = expander_node(node, no_env);
		string_push(&string, temp);
		free(temp);
		node = node->next;
	}
	return (expander_merge(&string, node, no_env));
}
