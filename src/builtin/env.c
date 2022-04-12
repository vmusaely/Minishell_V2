#include "minishell.h"

int	builtin_env(void)
{
	char	**env;

	env = env_to_string(false);
	argument_print(env, "");
	argument_destroy(env);
	return (0);
}
