#include "../parsing.h"

void	free_all(t_shell *minishell)
{
	t_node	*tmp;

	while (minishell->head && minishell->head != NULL)
	{
		tmp = minishell->head;
		minishell->head = minishell->head->next;
		free(tmp);
	}
	free(minishell->value);
	free(minishell->var_search);
	free(minishell);
}
