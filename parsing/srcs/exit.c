#include "minishell.h"

void	exit_strerror(t_shell *minishell, char *error)
{
	printf("bash : %s\n", error);
	free(minishell);
	exit(0);
}

void	exit_perror(t_shell *minishell, char *error)
{
	perror(error);
	free(minishell);
	exit(0);
}

void	exit_error(t_shell *minishell)
{
	free(minishell);
	exit(0);
}
