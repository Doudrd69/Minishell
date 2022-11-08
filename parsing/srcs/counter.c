#include "../parsing.h"

void	count_ope(t_shell *minishell)
{
	int		i;
	t_node	*tmp;
	char	*str;

	tmp = minishell->head;
	while (tmp && tmp != NULL)
	{
		i = 0;
		str = (char *)(tmp->content);
		while (str[i] != '\0')
		{
			nbr_ope(minishell, str, &i);
			i++;
		}
		tmp = tmp->next;
	}
}

static void	count_pipe(int i, int *pipe, t_shell *minishell, char *str)
{
	if (str[i] == '\"' && minishell->quote != 1 && str[i - 1] != '\\')
		minishell->quote = 1;
	else if (str[i] == '\"' && minishell->quote != 0 && str[i - 1] != '\\')
		minishell->quote = 0;
	if (str[i] == '|' && minishell->quote == 1)
		;
	if (str[i] == '|' && minishell->quote == 0)
		(*pipe)++;
}

void	nbr_ope(t_shell *minishell, char *str, int *i)
{
	count_pipe(*i, &minishell->nbr_pipe, minishell, str);
	if (str[*i] == '<' && str[*i + 1] != '<')
		minishell->nbr_infile++;
	else if (str[*i] == '<' && str[*i + 1] == '<')
	{
		*i += 1;
		minishell->nbr_appendin++;
		return ;
	}
	if (str[*i] == '>' && str[*i + 1] != '>')
		minishell->nbr_outfile++;
	else if (str[*i] == '>' && str[*i + 1] == '>')
	{
		*i += 1;
		minishell->nbr_appendout++;
		return ;
	}
	if (str[*i] == '$')
		minishell->nbr_dollars++;
	if (str[*i] == '\"')
		minishell->nbr_dquote++;
	if (str[*i] == '\'')
		minishell->nbr_squote++;
}
