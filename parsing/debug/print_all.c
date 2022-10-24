#include "../parsing.h"

void	print_dlist(t_node **list, t_shell *minishell)
{
	t_node	*tmp;
	int		i;

	i = 1;
	tmp = (*list);
	while (tmp && tmp != NULL)
	{
		if (tmp->type != NULL)
		{
			printf("list[%d] =%s\ntype = %s\n\n", i, (char *)tmp->content, tmp->type);
		}
		else
			printf("list[%d] =%s\ntype = No Type\n\n", i, (char *)tmp->content);
		tmp = tmp->next;
		i++;
	}
	printf("list_size = %d\n\n", minishell->list_size);
}
