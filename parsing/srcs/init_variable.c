#include "../parsing.h"

void	init_variable(t_shell *minishell, int env_size, char **envp)
{
	minishell->cmd = NULL;
	minishell->env_search = envp;
	minishell->env_size = env_size;
	minishell->home_path = NULL;
	minishell->quote = 0;
	minishell->nbr_pipe = 0;
	minishell->nbr_redirr = 0;
	minishell->nbr_redirg = 0;
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
	minishell->tail = NULL;
	minishell->list_size = 0;
}
