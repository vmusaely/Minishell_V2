#include "minishell.h"

t_list	*list_create(char *value)
{
	t_list	*self;

	self = ft_calloc(1, sizeof(t_list));
	if (!self)
		return (NULL);
	self->value = ft_strdup(value);
	self->next = NULL;
	return (self);
}

t_list	*list_last(t_list *self)
{
	while (self != NULL && self->next != NULL)
		self = self->next;
	return (self);
}

t_list	*list_push(t_list *self, t_list *src)
{
	t_list	*last;

	if (self == NULL)
		return (src);
	last = list_last(self);
	last->next = src;
	return (self);
}

void	list_destroy(t_list *self)
{
	if (!self)
		return ;
	if (self->next)
		list_destroy(self->next);
	if (self->value)
		free(self->value);
	free(self);
}
