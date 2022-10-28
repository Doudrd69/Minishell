#include "../parsing.h"

static void	init_var_redirection(t_shell *minishell, int size)
{
	int	i;

	i = 0;
	minishell->tab_infile = (t_node **)malloc(sizeof(t_node *) * (size + 1));
	minishell->tab_outfile = (t_node **)malloc(sizeof(t_node *) * (size + 1));
	while (i <= size)
	{
		minishell->tab_infile[i] = NULL;
		minishell->tab_outfile[i] = NULL;
		i++;
	}
}

static void	classic_infile(char *str, int tab, t_shell *minishell, t_node **list)
{
	int	i;

	i = minishell->mod;
	if (str[i] == '<' && str[i + 1] != '\0' && str[i + 1] != '<')
	{
		printf("classic infile\n");
		search_infile(minishell, str, &(minishell->tab_infile[tab]), list);
	}
}

static void	append_infile(char *str, int tab, t_shell *minishell, t_node **list)
{
	int	i;

	i = minishell->mod;
	if (str[i] == '<' && str[i + 1] != '\0' && str[i + 1] == '<')
	{
		printf("append infile\n");
		search_heredoc(minishell, str, &(minishell->tab_infile[tab]), list);
		i++;
	}
}

static void	classic_outfile(char *str, int tab, t_shell *minishell)
{
	int	i;

	i = minishell->mod;
	tab += 0;
	if (str[i] == '>' && str[i + 1] != '\0' && str[i + 1] != '>')
		printf("classic outfile\n");
}

static void	append_outfile(char *str, int tab, t_shell *minishell)
{
	int	i;

	i = minishell->mod;
	tab += 0;
	if (str[i] == '>' && str[i + 1] != '\0' && str[i + 1] == '>')
	{
		i++;
		printf("append outfile\n");
	}
}

void	parse_redirections(t_shell *minishell)
{
	int		size;
	int		i;
	t_node	*list_cpy;
	char	*str;
	int		j;

	j = 0;
	i = 0;
	size = minishell->nbr_pipe + 1;
	init_var_redirection(minishell, size);
	list_cpy = minishell->head;
	while (list_cpy && list_cpy != NULL)
	{
		if (list_cpy->type == 'P')
			j++;
		str = (char *)(list_cpy->content);
		minishell->mod = -1;
		while (str[++(minishell->mod)] != '\0')
		{
			classic_infile(str, j, minishell, &list_cpy);
			if (minishell->mod != -1)
			{
				append_infile(str, j, minishell, &list_cpy);
				if (minishell->mod != -1)
				{
					classic_outfile(str, j, minishell);
					if (minishell->mod != -1)
						append_outfile(str, j, minishell);
				}
			}
			str = (char *)(list_cpy->content);
		}
		list_cpy = list_cpy->next;
	}
}
