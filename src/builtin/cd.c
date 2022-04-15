/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmusaely <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 15:28:49 by vmusaely          #+#    #+#             */
/*   Updated: 2022/04/15 15:28:51 by vmusaely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_cd(int argc, char **argv)
{
	int		i;
	char	*home;
	char	buffer[PATH_MAX];

	i = 0;
	if (argc > 1)
		home = argv[1];
	else
		home = env_get("HOME");
	getcwd(buffer, PATH_MAX);
	env_set("OLDPWD", buffer);
	if (chdir(home) != 0)
	{
		error_print_code(NAME, "cd", NULL);
		return (1);
	}
	getcwd(buffer, PATH_MAX);
	env_set("PWD", buffer);
	return (0);
}
