#include "minishell.h"

int	builtin_unset(int argc, char **argv)
{
	int	i;

	if (argc > 1)
	{
		i = 1;
		while (i < argc)
			env_unset(argv[i++]);
	}
	return (0);
}
