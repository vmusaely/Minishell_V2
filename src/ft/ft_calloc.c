/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmusaely <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 15:34:21 by vmusaely          #+#    #+#             */
/*   Updated: 2022/04/15 15:34:22 by vmusaely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_calloc(size_t el_num, size_t el_size)
{
	void	*ptr;

	if (el_num == 0 && el_size == 0)
	{
		el_num = 1;
		el_size = 1;
	}
	ptr = malloc(el_num * el_size);
	if (ptr)
		ft_memset(ptr, 0, el_num * el_size);
	return (ptr);
}
