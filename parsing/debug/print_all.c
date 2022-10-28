#include "../parsing.h"

void	print_dlist(t_node **list, t_node ***tab_infile, t_node ***tab_outfile, t_shell *minishell)
{
	t_node	*tmp;
	t_node	**tmp_tab;
	int		i;
	int		j;

	i = 1;
	tmp = (*list);
	tab_outfile += 0;
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
	tmp_tab = *tab_infile;
	while (tmp_tab[i] && tmp_tab[i] != NULL)
	{
		j = 0;
		tmp = (tmp_tab)[i];
		while (tmp && tmp != NULL)
		{
			printf("infile_list[%d][%d] =%s, type = %c, addr = %p\n", i, j, (char *)tmp->content, (char)(tmp->type), tmp);
			j++;
			tmp = tmp->next;
		}
		i++;
	}
	printf("list_size = %d\n\n", minishell->list_size);
}
