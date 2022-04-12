#include "minishell.h"

#define FORMAT "warning: delimited by end-of-file (wanted '%s')\n"

static char	*parser_obtain_heredoc(char *identifer)
{
	t_string	heredoc;
	char		*input;

	string_init(&heredoc);
	signal_heredoc();
	while (true)
	{
		input = readline("> ");
		if (!input || ft_strcmp(input, identifer) == 0)
		{
			if (input)
				free(input);
			else
				printf(FORMAT, identifer);
			break ;
		}
		string_move(&heredoc, input);
		string_push(&heredoc, "\n");
	}
	signal_ignore();
	return (string_freeze(&heredoc));
}

#undef FORMAT

static bool	parser_write_to_tmp(t_node *result, char *tmpfile, bool no_env)
{
	int		fd;
	char	*expanded;

	fd = open(tmpfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return (false);
	expanded = expander_word(result, no_env);
	if (!expanded)
		expanded = ft_strdup("");
	write(fd, expanded, ft_strlen(expanded));
	close(fd);
	free(expanded);
	node_destroy(result);
	return (true);
}

static t_node	*parser_heredoc_node(char *heredoc)
{
	t_lexer		lexer;
	t_parser	parser;
	t_token		*tokens;
	t_node		*nodes;

	lexer_init(&lexer, heredoc, true);
	tokens = lexer_lex(&lexer);
	parser_init(&parser, tokens->next);
	parser.heredoc = true;
	nodes = parser_simple_word(&parser);
	token_destroy(tokens);
	return (nodes);
}

static bool	parser_handle_heredoc(t_parser *self, char *tmpfile)
{
	char	*heredoc;
	char	*identifer;
	int		code;
	bool	no_env;

	no_env = parser_check2(self, T_QUOTE) != NULL;
	identifer = parser_get_identifer(self);
	if (!identifer)
		return (false);
	if (!no_env && ft_strchr(identifer, ' ') != NULL)
		no_env = true;
	if (fork() == 0)
	{
		heredoc = parser_obtain_heredoc(identifer);
		parser_write_to_tmp(parser_heredoc_node(heredoc), tmpfile, no_env);
		free(identifer);
		exit(0);
	}
	wait(&code);
	self->heredoc_exit = WEXITSTATUS(code);
	free(identifer);
	return (true);
}

t_node	*parser_heredoc(t_parser *self)
{
	char	*tmpfile;
	t_node	*result;

	if (self->heredoc_exit == 2)
		return (NULL);
	tmpfile = utils_get_tmp_path();
	if (!parser_handle_heredoc(self, tmpfile))
	{
		free(tmpfile);
		return (parser_error(self, "Failed to obtain heredoc", NULL));
	}
	if (!tmpfile)
		return (NULL);
	result = node_create(NODE_REDIRECTION);
	result->redirect_kind = R_LEFT;
	result->rhs = node_create_value(NODE_WORD, tmpfile);
	free(tmpfile);
	return (result);
}
