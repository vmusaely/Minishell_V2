/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmusaely <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 15:42:28 by vmusaely          #+#    #+#             */
/*   Updated: 2022/04/15 15:42:30 by vmusaely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*parser_match2(t_parser *self, t_token_kind kind)
{
	while (parser_check(self, T_WHITESPACE))
		parser_advance(self);
	return (parser_match(self, kind));
}

t_token	*parser_notmatch(t_parser *self, t_token_kind kind)
{
	if (!parser_check(self, kind))
		return (parser_advance(self));
	return (NULL);
}

t_token	*parser_check2(t_parser *self, t_token_kind kind)
{
	while (parser_check(self, T_WHITESPACE))
		parser_advance(self);
	return (parser_check(self, kind));
}

void	parser_init(t_parser *self, t_token *tokens)
{
	self->tokens = tokens;
	self->current = tokens;
	self->error = false;
	self->in_quote = false;
	self->is_env = false;
	self->heredoc = false;
	self->index = 0;
	self->heredoc_exit = 0;
}

t_node	*parser_error(t_parser *self, char *message, t_node *node)
{
	if (self->error)
		return (NULL);
	ft_putstr_fd("Parser error: ", 2);
	ft_putstr_fd(message, 2);
	ft_putchar_fd('\n', 2);
	if (node)
		node_destroy(node);
	self->error = true;
	return (NULL);
}
