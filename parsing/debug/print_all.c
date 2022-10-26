#include "../parsing.h"

void	print_dlist(t_node **list, t_shell *minishell)
{
	t_node	*tmp;
	int		i;
	int		j;

	i = 1;
	tmp = (*list);
	while (tmp && tmp != NULL)
	{
		if (tmp->type != 'N')
		{
			printf("list[%d] =%s\ntype = %c\n\n", i, (char *)tmp->content, tmp->type);
		}
		else
			printf("list[%d] =%s\ntype = No Type\n\n", i, (char *)tmp->content);
		tmp = tmp->next;
		i++;
	}
	i = 0;
	while (minishell->tab_infile[i] != NULL)
	{
		j = 0;
		tmp = minishell->tab_infile[i];
		while (tmp && tmp != NULL)
		{
			printf("infile_list[%d][%d] = %s\n", i, j, (char *)tmp);
			j++;
			tmp = tmp->next;
		}
		i++;
	}
	printf("list_size = %d\n\n", minishell->list_size);
}
