#include "minishell.h"

void	signal_do_nothing(int sig)
{
	(void)sig;
	rl_on_new_line();
	rl_redisplay();
}

void	signal_reprompt(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	signal_interupt(int sig)
{
	write(1, "\n", 1);
	exit(sig);
}
