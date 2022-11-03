#include "../parsing.h"

static void	add_back_file_list(t_node **tab_list, t_node *new)
{
	t_node	*list_cpy;

	list_cpy = *tab_list;
	if (new)
	{
		if (!list_cpy)
		{
			(*tab_list) = new;
		}
		else
		{
			while (list_cpy && list_cpy->next != NULL)
				list_cpy = list_cpy->next;
			list_cpy->next = new;
			new->prev = list_cpy;
			list_cpy = new;
		}
	}
}

static void	include_infile_list(t_node **tab_list, char *tmp)
{
	t_node	*list_cpy;

	list_cpy = *tab_list;
	add_back_file_list(tab_list, ft_dlstnew(tmp));
	list_cpy = *tab_list;
	while (list_cpy && list_cpy->next != NULL && list_cpy != NULL)
				list_cpy = list_cpy->next;
	list_cpy->type = 'C';
}

static void	delete_file_list(t_shell *minishell, t_node **list, char *cpy, char *str)
{
	int	i;
	int	j;

	i = minishell->mod;
	j = -1;
	while (++j < i)
		cpy[j] = str[j];
	printf("char =%s\n", str + j);
	while (str[++i] != '\0' && str[i] == ' ')
		i++;
	while (str[i] != '\0' && str[i] != ' ')
		i++;
	while (str[i] != '\0' && str[i] == ' ')
		i++;
	while (str[i] != '\0')
		cpy[j++] = str[i++];
	cpy[j] = '\0';
	if (j == 0)
		cpy = NULL;
	printf("cpy =%s|\n", cpy);
	include_dollar_list(minishell, list, cpy);
}

void	search_outfile(t_shell *minishell, char *str, t_node **tab_outfile, t_node **list)
{
	int		i;
	int		file;
	char	*tmp;
	char	*cpy;
	int		space;

	file = 0;
	i = minishell->mod;
	space = 0;
	while (str[++i] != '\0' && str[i] == ' ')
		space++;
	while (str[i] != '\0' && str[i] != ' ')
	{
		file++;
		i++;
	}
	tmp = malloc(sizeof(char) * (file + 2));
	cpy = malloc(sizeof(char) * ((ft_strlen(str) - (file) + 1)));
	tmp = cmd_cpy(tmp, str + (minishell->mod) + 1 + space, file + 1);
	printf("tmp =%s\n", tmp);
	include_infile_list(tab_outfile, tmp);
	delete_file_list(minishell, list, cpy, str);
	minishell->mod = -1;
	print_dlist(&minishell->head, &minishell->tab_infile, &minishell->tab_outfile, minishell);
}