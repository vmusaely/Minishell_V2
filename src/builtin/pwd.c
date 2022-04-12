#include "minishell.h"

int	builtin_pwd(void)
{
	char	buffer[PATH_MAX];

	if (getcwd(buffer, PATH_MAX) == NULL)
	{
		error_print_code(NAME, "pwd", NULL);
		return (1);
	}
	printf("%s\n", buffer);
	return (0);
}
