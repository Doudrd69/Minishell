
#include "../parsing.h"

static void	ft_next(t_shell *minishell)
{
	t_node	*list_cpy;

	list_cpy = minishell->head;
	minishell->head = minishell->head->next;
	minishell->head->prev = NULL;
	minishell->list_size -= 1;
	free (list_cpy);
}

static char	*ft_tmp(char *tmp, char *str, int j, int i)
{
	(tmp) = malloc(sizeof(char) * (i + 1));
	(tmp) = cmd_cpy((tmp), str + j, i + 1);
	(tmp)[i] = '\0';
	return (tmp);
}

static char	*ft_prev(char *tmp, char *str, int j, int i)
{
	tmp = malloc(sizeof(char) * (ft_strlen(str) - (j + i - 1)));
	tmp = cmd_cpy(tmp, str + j + i, ft_strlen(str) - (j + i - 1));
	(tmp)[ft_strlen(str) - (j + i)] = '\0';
	return (tmp);
}

static void	ft_gagne_place(t_shell *minishell, char *tmp
	, int *i, t_node **list_cpy)
{
	ft_dlstadd_back((&(minishell)), ft_dlstnew((void *)tmp));
	*list_cpy = (*list_cpy)->next;
	ft_dlstadd_back((&(minishell)), ft_dlstnew((void *)"|\0"));
	*list_cpy = (*list_cpy)->next;
	(*list_cpy)->type = 'P';
	(*i)++;
}

void	parse_pipe(t_shell *minishell, int j, int i)
{
	int		pipe;
	char	*str;
	char	*tmp;
	t_node	*list_cpy;

	pipe = minishell->nbr_pipe;
	str = (char *)(minishell->head->content);
	list_cpy = minishell->head;
	while (str[++i + j] != '\0')
	{
		if (str[i + j] == '|'
			&& check_quote_pipe(minishell, str + i + j, i + j, &pipe) == 1)
		{
			tmp = ft_tmp(tmp, str, j, i);
			ft_gagne_place(minishell, tmp, &i, &list_cpy);
			if (pipe == 0 && str[i + j] != '\0')
			{
				tmp = ft_prev(tmp, str, j, i);
				ft_dlstadd_back((&(minishell)), ft_dlstnew((void *)tmp));
			}
			ft_incr_var_pipe(&j, &i);
		}
	}
	ft_next(minishell);
}
