#include "minishell.h"

void	parse_redirections(char *str, t_shell *minishell)
{
	int	i;

	i = -1;
	minishell += 0;
	while (str[++i] != '\0')
	{
		if (str[i] == '<')
		{
			printf("<%i", i);
		}
	}
}
