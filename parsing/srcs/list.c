#include "../parsing.h"

int	empty_list(t_shell *minishell)
{
	if (minishell->list_size == 0 && minishell->head == NULL
		&& minishell->tail == NULL)
		return (1);
	return (0);
}
