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
