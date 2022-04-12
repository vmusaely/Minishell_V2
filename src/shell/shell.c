#include "minishell.h"

t_shell	g_shell = (t_shell){0};

int	shell_builtin(int argc, char **argv)
{
	if (argc == 0)
		return (0);
	if (ft_strcmp(argv[0], "env") == 0)
		return (builtin_env());
	if (ft_strcmp(argv[0], "export") == 0)
		return (builtin_export(argc, argv));
	if (ft_strcmp(argv[0], "unset") == 0)
		return (builtin_unset(argc, argv));
	if (ft_strcmp(argv[0], "pwd") == 0)
		return (builtin_pwd());
	if (ft_strcmp(argv[0], "cd") == 0)
		return (builtin_cd(argc, argv));
	if (ft_strcmp(argv[0], "exit") == 0)
		return (builtin_exit(argc, argv));
	if (ft_strcmp(argv[0], "echo") == 0)
		return (builtin_echo(argc, argv));
	return (shell_bin(argv));
}

int	shell_command(t_node *command)
{
	char	**argv;
	int		argc;
	int		code;

	if ((command->kind & NODE_PIPE) != 0)
		code = shell_pipe(command);
	else if ((command->kind & NODE_REDIRECTION) != 0)
		code = shell_redirection(command);
	else
	{
		argv = expander_expand(command->arguments);
		argc = argument_size(argv);
		code = shell_builtin(argc, argv);
		if (argv && argc > 0)
			env_set("_", argv[argc - 1]);
		argument_destroy(argv);
	}
	if (command->next)
		code = shell_command(command->next);
	return (code);
}

int	shell_execute(char *input)
{
	t_token	*tokens;
	t_node	*node;
	int		code;

	if (ft_strlen(input) == 0)
		return (0);
	code = 2;
	lexer_init(&g_shell.lexer, input, false);
	tokens = lexer_lex(&g_shell.lexer);
	if (tokens && !g_shell.lexer.error)
	{
		node = parser_parse(&g_shell.parser, tokens);
		if (!g_shell.parser.error && node && g_shell.parser.heredoc_exit != 2)
			code = shell_command(node);
		node_destroy(node);
	}
	token_destroy(tokens);
	return (code);
}

void	shell_init(char **envp)
{
	size_t	i;

	env_init();
	g_shell.code = ft_strdup("0");
	i = 0;
	while (envp[i] != NULL)
		env_from_string(envp[i++]);
}

int	shell_start(void)
{
	char	*input;
	int		code;

	while (true)
	{
		input = readline("minishell $ ");
		if (!input)
		{
			printf("\n");
			break ;
		}
		if (ft_strlen(input) > 0)
			add_history(input);
		signal_ignore();
		code = shell_execute(input);
		if (g_shell.code)
			free(g_shell.code);
		g_shell.code = ft_itoa(code);
		signal_shell();
		free(input);
	}
	if (g_shell.code)
		free(g_shell.code);
	env_deinit();
	return (0);
}
