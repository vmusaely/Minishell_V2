/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_kind_to_string.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmusaely <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 15:44:09 by vmusaely          #+#    #+#             */
/*   Updated: 2022/04/15 15:44:10 by vmusaely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static const char	*token_kind_to_string_symbols(t_token_kind kind)
{
	if ((kind & T_DOLLAR_SIGN) != 0)
		return ("T_DOLLAR_SIGN");
	if ((kind & T_LESS) != 0)
		return ("T_LESS");
	if ((kind & T_GREAT) != 0)
		return ("T_GREAT");
	if ((kind & T_DOUBLE_LESS) != 0)
		return ("T_DOUBLE_LESS");
	if ((kind & T_DOUBLE_GREAT) != 0)
		return ("T_DOUBLE_GREAT");
	if ((kind & T_VERTICAL_BAR) != 0)
		return ("T_VERTICAL_BAR");
	if ((kind & T_SEMICOLON) != 0)
		return ("T_SEMICOLON");
	return ("T_UNKNOWN");
}

const char	*token_kind_to_string(t_token_kind kind)
{
	if ((kind & T_BEGIN) != 0)
		return ("T_BEGIN");
	if ((kind & T_QUOTE) != 0)
		return ("T_QUOTE");
	if ((kind & T_WHITESPACE) != 0)
		return ("T_WHITESPACE");
	if ((kind & T_WORD) != 0)
		return ("T_WORD");
	if ((kind & T_EOF) != 0)
		return ("T_EOF");
	return (token_kind_to_string_symbols(kind));
}

size_t	token_total_size(t_token *token)
{
	size_t	size;

	size = 0;
	while (token)
	{
		size += ft_strlen(token->slice);
		token = token->next;
	}
	return (size);
}
