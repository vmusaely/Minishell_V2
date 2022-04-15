/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmusaely <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 15:36:34 by vmusaely          #+#    #+#             */
/*   Updated: 2022/04/15 15:36:36 by vmusaely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_realloc(void *ptr, size_t size)
{
	void	*new_ptr;

	if (!ptr)
		return (malloc(size + 1));
	if (!size)
		return (ptr);
	new_ptr = malloc(size + 1);
	ft_memcpy(new_ptr, ptr, size);
	free(ptr);
	return (new_ptr);
}
