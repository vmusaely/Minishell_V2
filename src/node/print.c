#include "minishell.h"

const char	*node_kind_to_string(t_node_kind kind)
{
	if ((kind & NODE_COMMAND) != 0)
		return ("NODE_COMMAND");
	if ((kind & NODE_WORD) != 0)
		return ("NODE_WORD");
	if ((kind & NODE_VARIABLE) != 0)
		return ("NODE_VARIABLE");
	if ((kind & NODE_QUOTED) != 0)
		return ("NODE_QUOTED");
	if ((kind & NODE_PIPE) != 0)
		return ("NODE_PIPE");
	if ((kind & NODE_REDIRECTION) != 0)
		return ("NODE_REDIRECTION");
	return ("NODE_UNKNOWN");
}

static void	node_print_redirect(t_node *self, int indent)
{
	if ((self->redirect_kind & R_NONE) == 0)
	{
		node_print_indent(indent);
		printf("redirect:\n");
		node_print_indent(indent + 1);
		printf("kind: %s\n", redirect_kind_to_string(self->redirect_kind));
	}
}

void	node_print(t_node *self, int indent)
{
	if (!self)
		return ;
	node_print_indent(indent++);
	printf("@%s\n", node_kind_to_string(self->kind));
	node_print_value("value", self->value, indent);
	node_print_children(self->arguments, "arguments", indent);
	node_print_children(self->in_quote, "in_quote", indent);
	node_print_children(self->lhs, "lhs", indent);
	node_print_children(self->rhs, "rhs", indent);
	node_print_children(self->merged, "merged", indent - 1);
	node_print_redirect(self, indent);
	node_print_children(self->next, "next", indent - 1);
}
