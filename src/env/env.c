#include "minishell.h"

char	**env_to_string(bool export_command)
{
	size_t	i;
	size_t	j;
	t_env	*entry;
	char	**result;

	result = ft_calloc(TABLE_SIZE, sizeof(char *));
	i = 0;
	j = 0;
	while (i < TABLE_SIZE)
	{
		entry = g_shell.env[i++];
		while (entry)
		{
			if (export_command || entry->value != NULL)
				result[j++] = env_item_to_string(entry, export_command);
			entry = entry->next;
		}
	}
	result[j] = NULL;
	return (result);
}

void	env_set(char *key, char *value)
{
	size_t	bucket;
	t_env	*entry;
	t_env	*prev;

	bucket = env_hash(key);
	entry = g_shell.env[bucket];
	if (!entry)
	{
		g_shell.env[bucket] = env_pair(key, value);
		return ;
	}
	while (entry)
	{
		if (ft_strcmp(entry->key, key) == 0)
		{
			free(entry->value);
			entry->value = env_value_or_null(value);
			return ;
		}
		prev = entry;
		entry = entry->next;
	}
	prev->next = env_pair(key, value);
}

char	*env_get(char *key)
{
	size_t	bucket;
	t_env	*entry;

	if (ft_strcmp(key, "?") == 0)
		return (g_shell.code);
	bucket = env_hash(key);
	entry = g_shell.env[bucket];
	while (entry)
	{
		if (ft_strcmp(entry->key, key) == 0)
			return (entry->value);
		entry = entry->next;
	}
	return (NULL);
}

void	env_init(void)
{
	size_t	i;

	if (g_shell.env)
		env_deinit();
	g_shell.env = malloc(TABLE_SIZE * sizeof(t_env));
	i = 0;
	while (i < TABLE_SIZE)
		g_shell.env[i++] = NULL;
}

void	env_deinit(void)
{
	size_t	i;

	if (!g_shell.env)
		return ;
	i = 0;
	while (i < TABLE_SIZE)
	{
		if (g_shell.env[i] != NULL)
			env_destroy(g_shell.env[i]);
		++i;
	}
	free(g_shell.env);
	g_shell.env = NULL;
}
