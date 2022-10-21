#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_shell	*minishell;

	if (argc == 100)
		return (1);
	argv += 0;
	while (1)
	{
		minishell = malloc(sizeof(t_shell));
		init_variable(minishell, env);
		minishell->cmd = readline("/!\\ MINICOQUILLAGE /!\\ :");
		parsing(env, minishell);
		free_all(minishell);
	}
	return (0);
}

void	free_all(t_shell *minishell)
{
	t_node	*tmp;

	while (minishell->head && minishell->head != NULL)
	{
		tmp = minishell->head;
		minishell->head = minishell->head->next;
		free(tmp);
	}
	free(minishell->value);
	free(minishell->var_search);
	free(minishell);
}
