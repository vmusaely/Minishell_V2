#include "minishell.h"

static char	*shell_bin_exists(char *path, char *filename)
{
	t_string	temp;

	string_init(&temp);
	string_push(&temp, path);
	string_push(&temp, "/");
	string_push(&temp, filename);
	if (access(temp.buffer, F_OK) == 0)
		return (string_freeze(&temp));
	string_deinit(&temp);
	return (NULL);
}

static char	*shell_find_bin(char *f)
{
	char	**paths;
	size_t	i;
	char	*found;

	if (!f || ft_strlen(f) == 0)
		return (NULL);
	if ((f[0] == '/' || f[0] == '.') && access(f, F_OK) == 0)
		return (ft_strdup(f));
	paths = ft_split(env_get("PATH"), ':');
	i = 0;
	found = NULL;
	while (paths && paths[i] != NULL)
	{
		if (!found)
			found = shell_bin_exists(paths[i], f);
		free(paths[i++]);
	}
	free(paths);
	return (found);
}

static int	shell_get_code(int code)
{
	if (WIFSIGNALED(code))
	{
		if (WTERMSIG(code) == 3)
			ft_putstr_fd("Quit: 3\n", STDERR_FILENO);
		else if (WTERMSIG(code) == 2)
			ft_putstr_fd("\n", STDERR_FILENO);
		return (128 + WTERMSIG(code));
	}
	return (WEXITSTATUS(code));
}

int	shell_bin(char **argv)
{
	char	*path;
	int		code;
	char	**envp;

	path = shell_find_bin(argv[0]);
	if (!path)
	{
		error_print(NAME, argv[0], "command not found", NULL);
		return (127);
	}
	envp = env_to_string(false);
	if (fork() == 0)
	{
		signal_default();
		execve(path, argv, envp);
		error_print_code(NAME, "execvp", NULL);
		exit(1);
	}
	wait(&code);
	free(path);
	argument_destroy(envp);
	return (shell_get_code(code));
}
