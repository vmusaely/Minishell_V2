/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmusaely <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 15:42:12 by vmusaely          #+#    #+#             */
/*   Updated: 2022/04/15 15:42:15 by vmusaely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*parser_get_identifer(t_parser *self)
{
	t_node	*identifer;
	char	*string;

	identifer = parser_word(self);
	if (!identifer)
		return (NULL);
	string = expander_word(identifer, true);
	node_destroy(identifer);
	return (string);
}
