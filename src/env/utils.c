/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmusaely <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 15:33:04 by vmusaely          #+#    #+#             */
/*   Updated: 2022/04/15 15:33:08 by vmusaely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*env_pair(char *key, char *value)
{
	t_env	*env;

	env = ft_calloc(1, sizeof(t_env));
	if (!env)
		return (NULL);
	env->key = ft_strdup(key);
	env->value = env_value_or_null(value);
	env->next = NULL;
	return (env);
}

size_t	env_hash(char *key)
{
	size_t	value;
	size_t	length;
	size_t	i;

	value = 0;
	length = ft_strlen(key);
	i = 0;
	while (i < length)
		value *= 37 + key[i++];
	return (value % TABLE_SIZE);
}

void	env_destroy(t_env *env)
{
	if (!env)
		return ;
	if (env->next)
		env_destroy(env->next);
	if (env->key)
		free(env->key);
	if (env->value)
		free(env->value);
	free(env);
}

void	env_unset(char *key)
{
	size_t	bucket;
	t_env	*entry;
	t_env	*prev;

	bucket = env_hash(key);
	entry = g_shell.env[bucket];
	prev = NULL;
	while (entry)
	{
		if (ft_strcmp(entry->key, key) == 0)
		{
			if (prev)
				prev->next = entry->next;
			free(entry->key);
			free(entry->value);
			free(entry);
			if (!prev)
				g_shell.env[bucket] = NULL;
			return ;
		}
		prev = entry;
		entry = entry->next;
	}
}

char	*env_item_to_string(t_env *env, bool export_command)
{
	t_string	string;

	string_init(&string);
	string_push(&string, env->key);
	if (env->value != NULL)
	{
		string_push(&string, "=");
		if (export_command)
			string_push(&string, "\"");
		string_push(&string, env->value);
		if (export_command)
			string_push(&string, "\"");
	}
	return (string_freeze(&string));
}
