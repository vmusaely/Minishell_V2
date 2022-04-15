/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmusaely <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 15:43:15 by vmusaely          #+#    #+#             */
/*   Updated: 2022/04/15 15:43:16 by vmusaely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	shell_get_flag(t_redirect_kind kind)
{
	int	flags;

	if ((kind & R_LEFT) != 0)
		return (O_RDONLY);
	flags = O_CREAT | O_WRONLY;
	if ((kind & R_DOUBLE_RIGHT) != 0)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	return (flags);
}

static int	shell_get_fd(t_redirect_kind kind)
{
	if ((kind & R_LEFT) != 0)
		return (STDIN_FILENO);
	return (STDOUT_FILENO);
}

int	shell_redirection(t_node *command)
{
	char	*tfile;
	int		code;
	int		fd;

	tfile = expander_word(command->rhs, false);
	if (!tfile)
		return (1);
	if (fork() == 0)
	{
		fd = open(tfile, shell_get_flag(command->redirect_kind), 0755);
		if (fd == -1)
		{
			error_print_code(NAME, tfile, NULL);
			exit(1);
		}
		dup2(fd, shell_get_fd(command->redirect_kind));
		close(fd);
		exit(shell_command(command->lhs));
	}
	wait(&code);
	if (ft_strncmp(tfile, SHELL_TMP, ft_strlen(SHELL_TMP)) == 0)
		unlink(tfile);
	free(tfile);
	return (code);
}
