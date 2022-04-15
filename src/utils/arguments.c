/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmusaely <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 15:44:29 by vmusaely          #+#    #+#             */
/*   Updated: 2022/04/15 15:44:30 by vmusaely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	argument_print(char **arguments, char *prefix)
{
	size_t	i;

	i = 0;
	while (arguments[i] != NULL)
		printf("%s%s\n", prefix, arguments[i++]);
}

void	argument_destroy(char **arguments)
{
	size_t	i;

	i = 0;
	while (arguments[i] != NULL)
		free(arguments[i++]);
	free(arguments);
}

int	argument_size(char **arguments)
{
	int	i;

	if (!arguments)
		return (0);
	i = 0;
	while (arguments[i] != NULL)
		++i;
	return (i);
}
