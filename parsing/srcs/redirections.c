#include "../parsing.h"

void	parse_redirections(t_shell *minishell)
{
	int		i;
	t_node	**tab;
	int		size;

	i = -1;
	size = minishell->nbr_infile + minishell->nbr_outfile
		+ minishell->nbr_heredocin + minishell->nbr_heredocout + 1;
	printf("redir = %d, %d, %d, %d\n", minishell->nbr_infile,
		minishell->nbr_outfile, minishell->nbr_heredocin,
		minishell->nbr_heredocout);
	tab = (t_node **)malloc(sizeof(t_node *) * (size));
}
