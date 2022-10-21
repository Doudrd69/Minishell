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
			nbr_ope(minishell, str[i]);
			i++;
		}
		tmp = tmp->next;
	}
}

void	nbr_ope(t_shell *minishell, char c)
{
	if (c == '|')
		minishell->nbr_pipe++;
	if (c == '<')
		minishell->nbr_redirr++;
	if (c == '>')
		minishell->nbr_redirg++;
	if (c == '$')
		minishell->nbr_dollars++;
	if (c == '\"')
		minishell->nbr_dquote++;
	if (c == '\'')
		minishell->nbr_squote++;
}
