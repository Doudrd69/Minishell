#include "../parsing.h"

static void	add_back_file_list(t_node **minishell, t_node *new)
{
	t_node	*list_cpy;

	list_cpy = *minishell;
	if (new)
	{
		if (!list_cpy)
		{
			list_cpy = new;
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

static void	include_infile_list(t_node **minishell, char *tmp)
{
	t_node	*list_cpy;

	add_back_file_list(minishell, ft_dlstnew(tmp));
	list_cpy = *minishell;
	while (list_cpy && list_cpy->next != NULL)
				list_cpy = list_cpy->next;
	printf("DEBUG\n");
	// list_cpy->type = 'C';
}

void	search_infile(t_shell *minishell, char *str, int tab)
{
	int		i;
	int		file;
	char	*tmp;

	file = 0;
	i = minishell->mod;
	while (str[++i] != '\0' && str[i] == ' ')
		file++;
	while (str[i++] != '\0' && str[i] != ' ')
		file++;
	tmp = malloc(sizeof(char) * (file + 1));
	tmp = cmd_cpy(tmp, str + (minishell->mod) + 1, file + 2);
	include_infile_list(&minishell->tab_infile[tab], tmp);
	printf("tmp = %s, file = %d\n", tmp, file);
	print_dlist(&minishell->head, minishell);
}
