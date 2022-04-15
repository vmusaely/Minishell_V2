/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmusaely <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 15:42:37 by vmusaely          #+#    #+#             */
/*   Updated: 2022/04/15 15:42:38 by vmusaely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*parser_quoted(t_parser *self)
{
	t_node	*in_quote;
	t_node	*result;

	self->in_quote = true;
	in_quote = NULL;
	while (parser_match(self, T_QUOTE | T_EOF) == NULL)
		in_quote = node_push(in_quote, parser_simple_word(self));
	self->in_quote = false;
	result = node_create(NODE_QUOTED);
	if (!result)
	{
		node_destroy(in_quote);
		return (NULL);
	}
	result->in_quote = in_quote;
	if (self->heredoc && self->current->kind != T_EOF)
		result->merged = parser_simple_word(self);
	else if (!self->heredoc && parser_check(self, T_WORD | T_DOLLAR_SIGN))
		result->merged = parser_word(self);
	return (result);
}

static t_token	*parser_get_word(t_parser *self)
{
	if (self->in_quote)
		return (parser_notmatch(self, T_QUOTE | T_EOF));
	if (self->heredoc)
		return (parser_notmatch(self, T_EOF));
	return (parser_match(self, T_EOF | T_WORD | T_WHITESPACE));
}

t_node	*parser_simple_word(t_parser *self)
{
	t_token	*word;
	t_node	*result;

	self->is_env = (parser_match(self, T_DOLLAR_SIGN) != NULL);
	word = parser_get_word(self);
	if (!word || word->kind == T_EOF)
	{
		if (self->is_env && (self->in_quote || parser_check2(self,
					T_EOF) != NULL))
			return (node_create_value(NODE_WORD, "$"));
		if (self->is_env && !self->in_quote)
			return (node_create_value(NODE_WORD, ""));
		return (NULL);
	}
	if (self->is_env)
		result = node_create(NODE_VARIABLE);
	else
		result = node_create(NODE_WORD);
	result->value = ft_strdup(word->slice);
	if (self->heredoc && self->current->kind != T_EOF)
		result->merged = parser_simple_word(self);
	else if (!self->heredoc && parser_check(self, T_WORD | T_DOLLAR_SIGN))
		result->merged = parser_word(self);
	return (result);
}

t_node	*parser_word(t_parser *self)
{
	t_node	*temp;
	t_token	*check;

	if (parser_match2(self, T_DOUBLE_LESS))
		return (parser_heredoc(self));
	check = parser_match2(self, T_LESS | T_GREAT | T_DOUBLE_GREAT);
	if (check)
		return (parser_redirection(self, check->kind));
	if (parser_match2(self, T_QUOTE))
		temp = parser_quoted(self);
	else
		temp = parser_simple_word(self);
	if (temp && (parser_check(self,
				T_WORD) != NULL || (!self->in_quote && parser_check(self,
					T_QUOTE) != NULL)))
		temp->merged = parser_word(self);
	return (temp);
}
