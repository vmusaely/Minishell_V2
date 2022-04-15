/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmusaely <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 15:36:59 by vmusaely          #+#    #+#             */
/*   Updated: 2022/04/15 15:37:01 by vmusaely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
