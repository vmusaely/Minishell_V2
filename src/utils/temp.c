#include "minishell.h"

char	*utils_get_tmp_path(void)
{
	static size_t	index = 0;
	t_string		string;

	string_init(&string);
	if (index + 1 >= SIZE_MAX)
		index = 0;
	string_push(&string, SHELL_TMP);
	string_move(&string, ft_itoa(index++));
	return (string_freeze(&string));
}
