#include "minishell.h"

void	signal_shell(void)
{
	signal(SIGINT, signal_reprompt);
	signal(SIGQUIT, SIG_IGN);
}

void	signal_default(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	signal_ignore(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	signal_heredoc(void)
{
	signal(SIGINT, signal_interupt);
	signal(SIGQUIT, signal_do_nothing);
}
