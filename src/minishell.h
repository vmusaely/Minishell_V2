#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

# define NAME "minishell"
# define SHELL_TMP "/tmp/minishell"

// LIBFT
void				*ft_memcpy(void *dest, const void *src, size_t num);
void				*ft_calloc(size_t el_num, size_t el_size);
void				*ft_realloc(void *ptr, size_t size);
size_t				ft_strlen(const char *str);
char				*ft_strdup(const char *s);
int					ft_strcmp(const char *str1, const char *str2);
int					ft_strncmp(const char *str1, const char *str2, size_t n);
void				*ft_calloc(size_t el_num, size_t el_size);
void				*ft_memset(void *buffer, int c, size_t size);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strchr(const char *str, int c);
long				ft_atoi(const char *str);
char				*ft_itoa(int value);
char				**ft_split(char const *s, char c);
void				ft_putstr_fd(const char *s, int fd);
void				ft_putchar_fd(char c, int fd);
int					ft_isdigit(int c);
int					ft_isalpha(int c);
int					ft_isalnum(int c);
int					ft_isspace(int c);

typedef struct s_string
{
	char			*buffer;
	size_t			size;
	size_t			capacity;
}					t_string;

void				string_init(t_string *self);
int					string_push(t_string *self, const char *src);
int					string_move(t_string *self, char *src);
int					string_deinit(t_string *self);
char				*string_freeze(t_string *self);

typedef struct s_list
{
	char			*value;
	struct s_list	*next;
}					t_list;

t_list				*list_create(char *value);
t_list				*list_last(t_list *self);
t_list				*list_push(t_list *self, t_list *src);
size_t				list_size(t_list *self);
char				**list_freeze(t_list *self);
void				list_destroy(t_list *self);

typedef enum e_token_kind
{
	T_BEGIN = 1 << 0,
	T_QUOTE = 1 << 1,
	T_WHITESPACE = 1 << 2,
	T_WORD = 1 << 3,
	T_DOLLAR_SIGN = 1 << 4,
	T_LESS = 1 << 5,
	T_GREAT = 1 << 6,
	T_DOUBLE_LESS = 1 << 7,
	T_DOUBLE_GREAT = 1 << 8,
	T_VERTICAL_BAR = 1 << 9,
	T_SEMICOLON = 1 << 10,
	T_EOF = 1 << 11
}					t_token_kind;

const char			*token_kind_to_string(t_token_kind kind);

typedef struct s_token
{
	t_token_kind	kind;
	char			*slice;
	struct s_token	*next;
}					t_token;

t_token				*token_create(t_token_kind kind, char *slice);
t_token				*token_last(t_token *self);
t_token				*token_push(t_token *self, t_token *src);
t_token				*token_size(t_token *self);
size_t				token_total_size(t_token *token);
void				token_destroy(t_token *self);
void				token_print(t_token *self);

typedef struct s_lexer
{
	t_token			*tokens;
	const char		*input;
	bool			in_quotes;
	bool			heredoc;
	bool			dollar_sign;
	bool			error;
	size_t			cursor;
	size_t			length;
}					t_lexer;

typedef int			(*t_check)(int);

void				lexer_init(t_lexer *self, const char *input, bool heredoc);
t_token				*lexer_lex(t_lexer *self);
t_token				*lexer_next(t_lexer *self);
char				lexer_peek(t_lexer *self, int index);
t_token				*lexer_single_quote(t_lexer *self);
t_token				*lexer_symbols(t_lexer *self, char peek);
t_token				*lexer_until(t_lexer *self, t_token_kind kind, t_check c);
int					lexer_is_word(int c);
char				*char_to_string(char c);

typedef enum e_node_kind
{
	NODE_COMMAND = 1 << 0,
	NODE_WORD = 1 << 1,
	NODE_VARIABLE = 1 << 2,
	NODE_QUOTED = 1 << 3,
	NODE_PIPE = 1 << 4,
	NODE_REDIRECTION = 1 << 5
}					t_node_kind;

const char			*node_kind_to_string(t_node_kind kind);

typedef enum e_redirect_kind
{
	R_NONE = 1 << 0,
	R_LEFT = 1 << 1,
	R_RIGHT = 1 << 2,
	R_DOUBLE_RIGHT = 1 << 3
}					t_redirect_kind;

t_redirect_kind		token_kind_to_redirect_kind(t_token_kind kind);
const char			*redirect_kind_to_string(t_redirect_kind kind);

typedef struct s_node
{
	t_node_kind		kind;
	t_redirect_kind	redirect_kind;
	struct s_node	*lhs;
	struct s_node	*rhs;
	struct s_node	*next;
	struct s_node	*arguments;
	struct s_node	*in_quote;
	struct s_node	*merged;
	char			*value;
}					t_node;

t_node				*node_create(t_node_kind kind);
t_node				*node_create_value(t_node_kind kind, char *value);
t_node				*node_last(t_node *self);
t_node				*node_push(t_node *self, t_node *src);
void				node_print(t_node *self, int indent);
void				node_destroy(t_node *self);
size_t				node_size(t_node *self);
void				node_print_indent(int indent);
void				node_print_children(t_node *node, char *name, int indent);
void				node_print_value(char *name, char *value, int indent);

typedef struct s_parser
{
	int				heredoc_exit;
	bool			error;
	bool			in_quote;
	bool			is_env;
	bool			heredoc;
	t_token			*tokens;
	t_token			*current;
	int				index;
}					t_parser;

void				parser_init(t_parser *self, t_token *tokens);
t_node				*parser_parse(t_parser *self, t_token *tokens);
t_token				*parser_advance(t_parser *self);
t_token				*parser_check(t_parser *self, t_token_kind kind);
t_token				*parser_check2(t_parser *self, t_token_kind kind);
t_token				*parser_match(t_parser *self, t_token_kind kind);
t_token				*parser_notmatch(t_parser *self, t_token_kind kind);
t_token				*parser_match2(t_parser *self, t_token_kind kind);
t_token				*parser_consume(t_parser *self, t_token_kind kind);
t_node				*parser_command_line(t_parser *self);
t_node				*parser_redirection(t_parser *self, t_token_kind kind);
t_node				*parser_pipe(t_parser *self);
t_node				*parser_heredoc(t_parser *self);
t_node				*parser_quoted(t_parser *self);
t_node				*parser_simple_command(t_parser *self);
t_node				*parser_word(t_parser *self);
t_node				*parser_simple_word(t_parser *self);
t_node				*parser_multiline(t_parser *self);
char				*parser_get_identifer(t_parser *self);
t_node				*parser_error(t_parser *self, char *message, t_node *node);

# define TABLE_SIZE 1000

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

void				env_init(void);
void				env_set(char *key, char *value);
void				env_unset(char *key);
char				*env_get(char *key);
void				env_deinit(void);
void				env_destroy(t_env *env);
t_env				*env_pair(char *key, char *value);
size_t				env_hash(char *key);
char				**env_to_string(bool export_command);
char				*env_item_to_string(t_env *env, bool export_command);
int					env_from_string(char *string);
char				*env_value_or_null(char *value);

typedef struct s_shell
{
	char			*code;
	t_lexer			lexer;
	t_parser		parser;
	t_env			**env;
}					t_shell;

extern t_shell		g_shell;

void				shell_init(char **envp);
int					shell_pipe(t_node *command);
int					shell_redirection(t_node *command);
int					shell_command(t_node *command);
int					shell_builtin(int argc, char **argv);
int					shell_bin(char **argv);
int					shell_start(void);
int					shell_execute(char *input);

t_list				*expander_from_env(t_list *list, char *env);
char				**expander_expand(t_node *node);
char				*expander_quoted(t_node *node, bool no_env);
char				*expander_simple_word(t_node *node, bool no_env);
char				*expander_word(t_node *node, bool no_env);
char				*expander_merge(t_string *temp, t_node *node, bool no_env);
char				*expander_node(t_node *node, bool no_env);

void				argument_print(char **arguments, char *prefix);
void				argument_destroy(char **arguments);
int					argument_size(char **arguments);

int					builtin_unset(int argc, char **argv);
int					builtin_export(int argc, char **argv);
int					builtin_echo(int argc, char **argv);
int					builtin_cd(int argc, char **argv);
int					builtin_exit(int argc, char **argv);
int					builtin_env(void);
int					builtin_pwd(void);

char				**shell_realpaths(const char *path);
char				*utils_get_tmp_path(void);

void				signal_do_nothing(int sig);
void				signal_reprompt(int sig);
void				signal_interupt(int sig);
void				signal_shell(void);
void				signal_default(void);
void				signal_ignore(void);
void				signal_heredoc(void);

void				error_print(char *msg1, char *msg2, char *msg3, char *msg4);
void				error_print_code(char *msg1, char *msg2, char *msg3);

#endif