/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmusaely <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 15:36:44 by vmusaely          #+#    #+#             */
/*   Updated: 2022/04/15 15:36:46 by vmusaely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	ft_wordcount(const char *s, char c)
{
	size_t	i;
	bool	is_word;

	i = 0;
	is_word = false;
	while (*s)
	{
		if (!is_word && *s != c)
			is_word = ((bool)++i);
		else if (is_word && *s == c)
			is_word = false;
		++s;
	}
	return (i);
}

static void	*ft_freeall(char **arr, size_t index)
{
	while (index-- > 0)
		free(arr[index]);
	free(arr);
	return (NULL);
}

static size_t	ft_strclen(const char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		++i;
	return (i);
}

char	**ft_split(char const *s, char c)
{
	size_t	index;
	size_t	word_count;
	size_t	arr_len;
	char	**arr;

	if (!s)
		return (NULL);
	index = 0;
	arr_len = 0;
	word_count = ft_wordcount(s, c);
	arr = malloc((word_count + 1) * sizeof(char *));
	while (*s && word_count--)
	{
		while (*s && *s == c)
			++s;
		arr_len = ft_strclen(s, c);
		arr[index] = ft_substr(s, 0, arr_len);
		if (!arr[index])
			return (ft_freeall(arr, index));
		s += arr_len;
		++index;
	}
	arr[index] = NULL;
	return (arr);
}
