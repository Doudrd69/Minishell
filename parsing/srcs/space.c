#include "../parsing.h"

static void	ft_prev(t_node *list_cpy, t_shell *minishell, t_node *tmp)
{
	list_cpy->next->prev = list_cpy;
	list_cpy->prev = NULL;
	minishell->head = list_cpy;
	free(tmp);
}

static void	ft_mid(t_node *list_cpy, t_node *tmp)
{
	list_cpy->next->prev = list_cpy;
	list_cpy->prev = tmp->prev;
	list_cpy->prev->next = list_cpy;
	free(tmp);
}

static void	ft_next(t_node *list_cpy, t_shell *minishell, t_node *tmp)
{
	if (tmp->prev != NULL)
	{
		list_cpy->prev = tmp->prev;
		list_cpy->prev->next = list_cpy;
	}
	else
	{
		list_cpy->prev = NULL;
		minishell->head = list_cpy;
	}
	free(tmp);
}

void	parse_space(t_shell *minishell)
{
	t_node	*list_cpy;
	t_node	*tmp;
	char	*str;
	char	**tab;
	int		j;

	list_cpy = minishell->head;
	while (list_cpy && list_cpy != NULL)
	{
		str = (char *)(list_cpy->content);
		tab = ft_split(str, ' ');
		j = -1;
		while (tab[++j] != NULL)
			list_nospace(minishell, &list_cpy, tab[j], j);
		tmp = list_cpy;
		list_cpy = list_cpy->next;
		if (tmp && tmp->prev != NULL && tmp->next->next != NULL)
			ft_mid(list_cpy, tmp);
		else if (tmp->prev == NULL && tmp->next->next != NULL)
			ft_prev(list_cpy, minishell, tmp);
		else
			ft_next(list_cpy, minishell, tmp);
		while (j-- >= 0 && list_cpy && list_cpy != NULL)
			list_cpy = list_cpy->next;
	}
}

void	list_nospace(t_shell *minishell, t_node **list, char *tmp, int j)
{
	t_node	*tmp_list;
	t_node	*new_node;
	t_node	*list_cpy;

	minishell += 0;
	tmp_list = (*list);
	while (j > 0)
	{
		tmp_list = tmp_list->next;
		j--;
	}
	if (tmp_list && tmp_list->next == NULL)
	{
		ft_dlstadd_back(&minishell, ft_dlstnew((void *)(tmp)));
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
