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

static void	include_heredoc_list(t_node **tab_list, char *tmp)
{
	t_node	*list_cpy;

	list_cpy = *tab_list;
	add_back_file_list(tab_list, ft_dlstnew(tmp));
	list_cpy = *tab_list;
	while (list_cpy && list_cpy->next != NULL && list_cpy != NULL)
				list_cpy = list_cpy->next;
	list_cpy->type = 'A';
}

static void	delete_file_list(t_shell *minishell, t_node **list, char *cpy, char *str)
{
	int	i;
	int	j;

	i = minishell->mod;
	j = -1;
	while (++j < i)
		cpy[j] = str[j];
	i++;
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
	include_dollar_list(minishell, list, cpy);
}

int	check_quote_heredoc(t_shell *minishell, char *str, int len)
{
	int	i;
	int	dquote;

	i = 0;
	dquote = 0;
	minishell->quote = 0;
	while (i < len + 1 && str[i] != '\0')
	{
		if (str[i] == '\"' && minishell->quote != 1 && str[i - 1] != '\\')
			minishell->quote = 1;
		else if (str[i] == '\"' && minishell->quote != 0 && str[i - 1] != '\\')
			minishell->quote = 0;
		if (str[i] == '\'' && dquote != 1 && str[i - 1] != '\\')
			dquote = 1;
		else if (str[i] == '\'' && dquote != 0 && str[i - 1] != '\\')
			dquote = 0;
		if (str[i] == '<' && str[i + 1] == '<'
			&& (minishell->quote == 1 || dquote == 1))
			return (0);
		if (str[i] == '<' && str[i + 1] == '<'
			&& (minishell->quote == 0 || dquote == 0))
			return (1);
		i++;
	}
	return (1);
}

void	search_heredoc(t_shell *minishell, char *str, t_node **tab_infile, t_node **list)
{
	int		i;
	int		file;
	char	*tmp;
	char	*cpy;

	file = 0;
	i = minishell->mod;
	i += 1;
	while (str[++i] != '\0' && str[i] == ' ')
		file++;
	while (str[i] != '\0' && str[i] != ' ')
	{
		file++;
		i++;
	}
	tmp = malloc(sizeof(char) * (file + 2));
	cpy = malloc(sizeof(char) * ((ft_strlen(str) - (file) + 1)));
	tmp = cmd_cpy(tmp, str + (minishell->mod + 1) + 1, file + 1);
	include_heredoc_list(tab_infile, tmp);
	delete_file_list(minishell, list, cpy, str);
	minishell->mod = -1;
	print_dlist(&minishell->head, &minishell->tab_infile, &minishell->tab_outfile, minishell);
}
