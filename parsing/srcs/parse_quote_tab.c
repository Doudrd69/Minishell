#include "../parsing.h"

static void	ft_prev(t_node *list_cpy, t_node *tmp, t_shell *minishell, int tab)
{
	list_cpy->next->prev = list_cpy;
	list_cpy->prev = NULL;
	(list_cpy)->type = tmp->type;
	minishell->tab_infile[tab] = list_cpy;
	free(tmp);
}

static void	ft_mid(t_node *list_cpy, t_node *tmp)
{
	list_cpy->next->prev = list_cpy;
	list_cpy->prev = tmp->prev;
	list_cpy->prev->next = list_cpy;
	(list_cpy)->type = tmp->type;
	free(tmp);
}

static void	ft_next(t_node **list_cpy, t_node *tmp, t_shell *minishell, int tab)
{
	if ((tmp)->prev != NULL)
	{
		(*list_cpy)->prev = (tmp)->prev;
		(*list_cpy)->prev->next = (*list_cpy);
		(*list_cpy)->type = tmp->type;
	}
	else
	{
		(*list_cpy)->prev = NULL;
		(*list_cpy)->type = tmp->type;
		minishell->tab_infile[tab] = *list_cpy;
	}
	free(tmp);
}

static void	list_nospace_tab(t_shell *minishell, t_node **list, char *tmp, int j)
{
	t_node	*tmp_list;
	t_node	*new_node;
	t_node	*list_cpy;

	tmp_list = (*list);
	minishell += 0;
	while (j > 0)
	{
		tmp_list = tmp_list->next;
		j--;
	}
	if (tmp_list && tmp_list->next == NULL)
	{
		add_back_file_list(list, ft_dlstnew(tmp));
		tmp_list = (*list);
	}
	else
	{
		list_cpy = tmp_list;
		new_node = ft_dlstnew((void *)(tmp));
		tmp_list = new_node;
		tmp_list->next = list_cpy->next;
		tmp_list->prev = list_cpy;
		tmp_list->next->prev = new_node;
		tmp_list->prev->next = new_node;
		list_cpy->next = tmp_list;
	}
}

void	parse_quote_tab(t_shell *minishell, t_node ***tab_infile, t_node ***tab_outfile)
{
	t_node	**intab;
	t_node	*list_cpy;
	t_node	*tmp;
	int		i;
	char	**tab;
	char	*str;
	int		j;

	tab_outfile += 0;
	minishell += 0;
	if (minishell->tab_infile != NULL)
	{
		i = 0;
		intab = *tab_infile;
		while (intab && intab[i] && intab[i] != NULL)
		{
			list_cpy = (intab)[i];
			while (list_cpy && list_cpy != NULL)
			{
				str = (char *)(list_cpy->content);
				tab = ft_split_minishell(minishell, str, ' ');
				j = -1;
				while (tab && tab[++j] != NULL)
					list_nospace_tab(minishell, &list_cpy, tab[j], j);
				tmp = list_cpy;
				if (tmp)
					list_cpy = list_cpy->next;
				if (tmp && tmp->prev != NULL && tmp->next->next != NULL)
				{
					ft_mid(list_cpy, tmp);
				}
				else if (tmp && tmp->prev == NULL && tmp->next->next != NULL)
				{
					ft_prev(list_cpy, tmp, minishell, i);
				}
				else if (tmp)
				{
					ft_next(&list_cpy, tmp, minishell, i);
				}
				while (j-- > 0 && list_cpy && list_cpy != NULL)
					list_cpy = list_cpy->next;
			}
			i++;
		}
	}
	ft_parse_quote_outab(minishell, tab_outfile);
}
