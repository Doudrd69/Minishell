#include "../minishell.h"

void	print_dlist(t_node **list)
{
	t_node	*tmp;

	tmp = (*list);
	while (tmp && tmp != NULL)
	{
		printf("%s*", (char *)tmp->content);
		tmp = tmp->next;
	}
	printf("\n");
}
