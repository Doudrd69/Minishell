#include "../parsing.h"

void	parse_redirections(t_shell *minishell)
{
	int		size;
	t_node	*list_cpy;
	char	*str;
	int		i;

	size = minishell->nbr_pipe + 1;
	printf("redir = %d, %d, %d, %d\n", minishell->nbr_infile,
		minishell->nbr_outfile, minishell->nbr_appendin,
		minishell->nbr_appendout);
	if (minishell->nbr_infile == 0 && minishell->nbr_appendin == 0)
		if (minishell->nbr_outfile == 0 && minishell->nbr_appendout == 0)
			return ;
	minishell->tab_infile = (t_node **)malloc(sizeof(t_node *) * (size + 1));
	minishell->tab_outfile = (t_node **)malloc(sizeof(t_node *) * (size + 1));
	list_cpy = minishell->head;
	while (list_cpy && list_cpy != NULL)
	{
		str = (char *)(list_cpy->content);
		i = 0;
		while (str[i] != '\0')
		{
			if (str[i] == '<')
				return ;
		}
	}
}
