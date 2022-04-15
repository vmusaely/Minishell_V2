/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmusaely <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 15:39:33 by vmusaely          #+#    #+#             */
/*   Updated: 2022/04/15 15:39:35 by vmusaely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*lexer_error(t_lexer *lexer, const char *message, char peek)
{
	lexer->error = true;
	ft_putstr_fd("Lexer error: ", 2);
	ft_putstr_fd(message, 2);
	if (peek)
	{
		ft_putstr_fd(" '", 2);
		ft_putchar_fd(peek, 2);
		ft_putchar_fd('\'', 2);
	}
	ft_putchar_fd('\n', 2);
	return (NULL);
}

t_token	*lexer_single_quote(t_lexer *self)
{
	int		start;
	int		length;
	char	*word;
	char	peek;
	t_token	*result;

	if (self->in_quotes || self->heredoc)
		return (token_create(T_WORD, ft_strdup("'")));
	result = token_create(T_QUOTE, ft_strdup("'"));
	start = self->cursor + 1;
	length = 1;
	peek = lexer_peek(self, length);
	while (peek != '\0' && peek != '\'')
		peek = lexer_peek(self, ++length);
	if (peek != '\'')
		return (lexer_error(self, "Unterminated string", 0));
	word = ft_substr(self->input, start, length - 1);
	result = token_push(result, token_create(T_WORD, word));
	return (token_push(result, token_create(T_QUOTE, ft_strdup("'"))));
}

t_token	*lexer_next(t_lexer *self)
{
	char	peek;
	t_token	*temp;

	peek = lexer_peek(self, 0);
	if (peek == '\0')
		return (NULL);
	temp = lexer_symbols(self, peek);
	if (temp)
		return (temp);
	if (peek == '"')
	{
		self->in_quotes = !self->in_quotes;
		return (token_create(T_QUOTE, ft_strdup("\"")));
	}
	if (peek == '\'')
		return (lexer_single_quote(self));
	if (ft_isspace(peek))
		return (lexer_until(self, T_WHITESPACE, ft_isspace));
	if (ft_isalpha(peek))
		return (lexer_until(self, T_WORD, ft_isalnum));
	if (!self->in_quotes && ft_strchr("()[]", peek))
		return (lexer_error(self, "unexpected token", peek));
	return (token_create(T_WORD, char_to_string(peek)));
}

void	lexer_init(t_lexer *self, const char *input, bool heredoc)
{
	self->cursor = 0;
	self->error = false;
	self->heredoc = heredoc;
	self->in_quotes = false;
	self->dollar_sign = false;
	self->input = input;
	self->length = ft_strlen(input);
	self->tokens = token_create(T_BEGIN, NULL);
}

t_token	*lexer_lex(t_lexer *self)
{
	t_token	*next;

	next = lexer_next(self);
	while (next && self->error == false)
	{
		self->dollar_sign = (next->kind == T_DOLLAR_SIGN);
		self->cursor += token_total_size(next);
		token_push(self->tokens, next);
		next = lexer_next(self);
	}
	if (self->in_quotes && !self->heredoc)
		lexer_error(self, "Unterminated string", 0);
	token_push(self->tokens, token_create(T_EOF, NULL));
	return (self->tokens);
}
