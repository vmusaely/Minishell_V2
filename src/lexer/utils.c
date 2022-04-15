/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmusaely <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 15:39:49 by vmusaely          #+#    #+#             */
/*   Updated: 2022/04/15 15:39:52 by vmusaely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lexer_is_word(int c)
{
	return (!ft_strchr(" \t$=|><;$\"'", c));
}

char	lexer_peek(t_lexer *self, int index)
{
	if (self->cursor + index >= self->length)
		return ('\0');
	return (self->input[self->cursor + index]);
}

t_token	*lexer_until(t_lexer *self, t_token_kind kind, t_check check)
{
	int		length;
	char	peek;
	int		start;
	char	*result;

	length = 1;
	start = self->cursor;
	peek = lexer_peek(self, length);
	while (peek != '\0' && check(peek))
		peek = lexer_peek(self, ++length);
	result = ft_substr(self->input, start, length);
	return (token_create(kind, result));
}
