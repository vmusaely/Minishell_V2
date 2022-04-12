#include "minishell.h"

t_node	*node_create(t_node_kind kind)
{
	t_node	*node;

	node = ft_calloc(1, sizeof(t_node));
	if (!node)
		return (NULL);
	node->kind = kind;
	node->lhs = NULL;
	node->rhs = NULL;
	node->next = NULL;
	node->arguments = NULL;
	node->in_quote = NULL;
	node->value = NULL;
	node->merged = NULL;
	node->redirect_kind = R_NONE;
	return (node);
}

t_node	*node_last(t_node *self)
{
	while (self != NULL && self->next != NULL)
		self = self->next;
	return (self);
}

t_node	*node_push(t_node *self, t_node *src)
{
	t_node	*last;

	if (self == NULL)
		return (src);
	last = node_last(self);
	last->next = src;
	return (self);
}

void	node_destroy(t_node *self)
{
	if (self == NULL)
		return ;
	if (self->arguments != NULL)
		node_destroy(self->arguments);
	if (self->next != NULL)
		node_destroy(self->next);
	if (self->in_quote != NULL)
		node_destroy(self->in_quote);
	if (self->value != NULL)
		free(self->value);
	if (self->merged != NULL)
		node_destroy(self->merged);
	if (self->lhs != NULL)
		node_destroy(self->lhs);
	if (self->rhs != NULL)
		node_destroy(self->rhs);
	free(self);
}

size_t	node_size(t_node *self)
{
	size_t	size;

	if (!self)
		return (0);
	size = 1;
	while (self->next)
	{
		size++;
		self = self->next;
	}
	return (size);
}
