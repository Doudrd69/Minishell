#include "../parsing.h"

static void	classic_infile(char *str, int tab, t_shell *minishell,
	t_node **list)
{
	int	i;

	i = minishell->mod;
	if (i == -1)
		return ;
	if (str[i] == '<' && str[i + 1] == '\0')
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		exit(0);
	}
	if (str[i] == '<' && str[i + 1] != '\0' && str[i + 1] != '<'
		&& check_quote_infile(minishell, str, strlen(str)) == 1)
	{
		minishell->infile_size = tab;
		search_infile(minishell, str, &(minishell->tab_infile[tab]), list);
	}
}

static void	append_infile(char *str, int tab, t_shell *minishell, t_node **list)
{
	int	i;

	i = minishell->mod;
	if (i == -1)
		return ;
	if (str[i] == '<' && str[i + 1] == '<' && str[i + 2] == '\0')
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		exit(0);
	}
	if (str[i] == '<' && str[i + 1] != '\0' && str[i + 1] == '<'
		&& check_quote_heredoc(minishell, str, strlen(str)) == 1)
	{
		minishell->infile_size = tab;
		search_heredoc(minishell, str, &(minishell->tab_infile[tab]), list);
		i++;
	}
}

static void	classic_outfile(char *str, int tab, t_shell *minishell,
	t_node **list)
{
	int	i;

	i = minishell->mod;
	if (i == -1)
		return ;
	if (str[i] == '>' && str[i + 1] == '\0')
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		exit(0);
	}
	if (str[i] == '>' && str[i + 1] != '\0' && str[i + 1] != '>'
		&& check_quote_outfile(minishell, str, strlen(str)) == 1)
	{
		minishell->outfile_size = tab;
		search_outfile(minishell, str, &(minishell->tab_outfile[tab]), list);
	}
}

static void	append_outfile(char *str, int tab, t_shell *minishell,
	t_node **list)
{
	int	i;

	i = minishell->mod;
	if (i == -1)
		return ;
	if (str[i] == '>' && str[i + 1] == '>' && str[i + 2] == '\0')
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		exit(0);
	}
	if (str[i] == '>' && str[i + 1] != '\0' && str[i + 1] == '>'
		&& check_quote_append(minishell, str, strlen(str)) == 1)
	{
		minishell->outfile_size = tab;
		search_append(minishell, str, &(minishell->tab_outfile[tab]), list);
		i++;
	}
}

void	parse_redirections(t_shell *minishell)
{
	int		size;
	t_node	*list_cpy;
	char	*str;
	int		j;

	j = 0;
	size = minishell->nbr_pipe + 1;
	init_var_redirection(minishell, size);
	list_cpy = minishell->head;
	while (list_cpy && list_cpy != NULL)
	{
		if (list_cpy->type == 'P')
			j++;
		str = (char *)(list_cpy->content);
		minishell->mod = -1;
		while (str && str[++(minishell->mod)] != '\0')
		{
			classic_infile(str, j, minishell, &list_cpy);
			append_infile(str, j, minishell, &list_cpy);
			classic_outfile(str, j, minishell, &list_cpy);
			append_outfile(str, j, minishell, &list_cpy);
			str = (char *)(list_cpy->content);
		}
		list_cpy = list_cpy->next;
	}
}
