/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmusaely <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 15:35:59 by vmusaely          #+#    #+#             */
/*   Updated: 2022/04/15 15:36:00 by vmusaely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_memset(void *buffer, int c, size_t size)
{
	char			*cb;
	unsigned int	i;

	cb = buffer;
	i = 0;
	while (i < size)
		cb[i++] = c;
	return (cb);
}
