#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	shell_init(envp);
	if (argc > 2 && ft_strcmp(argv[1], "-c") == 0)
		return (shell_execute(argv[2]));
	signal_shell();
	return (shell_start());
}
