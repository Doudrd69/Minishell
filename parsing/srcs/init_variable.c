#include "../parsing.h"

void	init_variable(t_shell *minishell, int env_size, char **envp)
{
	minishell->cmd = NULL;
	minishell->env_search = envp;
	minishell->env_size = env_size;
	minishell->home_path = NULL;
	minishell->quote = 0;
	minishell->nbr_pipe = 0;
	minishell->nbr_infile = 0;
	minishell->nbr_outfile = 0;
	minishell->nbr_appendin = 0;
	minishell->nbr_appendout = 0;
	minishell->nbr_dollars = 0;
	minishell->nbr_dquote = 0;
	minishell->nbr_squote = 0;
	minishell->envp = envp;
	minishell->value = NULL;
	minishell->var_search = NULL;
	init_dlist_var(minishell);
}

void	init_dlist_var(t_shell *minishell)
{
	minishell->head = NULL;
	minishell->tab_infile = NULL;
	minishell->tab_outfile = NULL;
	minishell->tail = NULL;
	minishell->list_size = 0;
}
