#include "minishell.h"

static void	shell_close_pfd(int pfd[2])
{
	close(pfd[0]);
	close(pfd[1]);
}

static void	shell_dup2(int pfd[2], int fd, int fd2)
{
	dup2(fd, fd2);
	shell_close_pfd(pfd);
}

int	shell_pipe(t_node *command)
{
	int	pfd[2];
	int	code;

	if (pipe(pfd) == -1)
		return (1);
	if (fork() == 0)
	{
		shell_dup2(pfd, pfd[1], STDOUT_FILENO);
		exit(shell_command(command->lhs));
	}
	wait(&code);
	if (fork() == 0)
	{
		shell_dup2(pfd, pfd[0], STDIN_FILENO);
		exit(shell_command(command->rhs));
	}
	shell_close_pfd(pfd);
	wait(&code);
	return (code);
}
