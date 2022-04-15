/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmusaely <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 15:29:20 by vmusaely          #+#    #+#             */
/*   Updated: 2022/04/15 15:29:22 by vmusaely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exit_check(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	builtin_exit(int argc, char **argv)
{
	long	value;

	ft_putstr_fd("exit\n", STDERR_FILENO);
	value = 0;
	if (argc >= 2)
	{
		value = ft_atoi(argv[1]);
		if (!exit_check(argv[1]) || value > INT_MAX || value < INT_MIN)
		{
			error_print(NAME, "exit", argv[1], "numeric argument required");
			exit(2);
		}
	}
	exit(value);
	return (0);
}
