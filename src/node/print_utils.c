#include "minishell.h"

void	node_print_indent(int indent)
{
	indent *= 2;
	while (indent-- > 0)
		printf(" ");
}

void	node_print_children(t_node *node, char *name, int indent)
{
	if (node)
	{
		node_print_indent(indent);
		printf("%s:\n", name);
		node_print(node, indent + 1);
	}
}

void	node_print_value(char *name, char *value, int indent)
{
	if (name && value)
	{
		node_print_indent(indent);
		printf("%s: '%s'\n", name, value);
	}
}

t_node	*node_create_value(t_node_kind kind, char *value)
{
	t_node	*node;

	node = node_create(kind);
	if (!node)
		return (NULL);
	node->value = ft_strdup(value);
	return (node);
}
