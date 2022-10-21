#include "minishell.h"

void	free_all(t_shell *minishell)
{
	ft_free_list(minishell->envp);
	free(minishell);
}

void	ft_free_list(t_var *list_a)
{
	t_var	*tempi;
	t_var	*temple;

	if (!(list_a))
		return ;
	tempi = list_a;
	temple = list_a;
	while (tempi)
	{
		temple = temple->next;
		free(tempi);
		tempi = temple;
	}
	free(tempi);
	list_a = NULL;
}
