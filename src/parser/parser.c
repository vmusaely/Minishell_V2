/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmusaely <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 15:42:21 by vmusaely          #+#    #+#             */
/*   Updated: 2022/04/15 15:42:23 by vmusaely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*parser_parse(t_parser *self, t_token *tokens)
{
	parser_init(self, tokens);
	if (!parser_consume(self, T_BEGIN))
		return (NULL);
	return (parser_command_line(self));
}

t_token	*parser_advance(t_parser *self)
{
	t_token	*temp;

	temp = self->current;
	if (self->current->kind != T_EOF)
	{
		self->current = self->current->next;
		self->index++;
	}
	return (temp);
}

t_token	*parser_check(t_parser *self, t_token_kind kind)
{
	if ((self->current->kind & kind) != 0)
		return (self->current);
	return (NULL);
}

t_token	*parser_match(t_parser *self, t_token_kind kind)
{
	if (parser_check(self, kind))
		return (parser_advance(self));
	return (NULL);
}

t_token	*parser_consume(t_parser *self, t_token_kind kind)
{
	if (self->error)
		return (NULL);
	if (parser_check(self, kind) != NULL)
		return (parser_advance(self));
	ft_putstr_fd("Parser error: Expected ", 2);
	ft_putstr_fd(token_kind_to_string(kind), 2);
	ft_putstr_fd(", but got ", 2);
	ft_putstr_fd(token_kind_to_string(self->current->kind), 2);
	ft_putstr_fd(".\n", 2);
	self->error = true;
	return (NULL);
}
