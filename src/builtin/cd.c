#include "minishell.h"

int	builtin_cd(int argc, char **argv)
{
	char	*home;

	if (argc > 1)
		home = argv[1];
	else
		home = getenv("HOME");
	if (chdir(home) != 0)
	{
		error_print_code(NAME, "cd", NULL);
		return (1);
	}
	return (0);
}
