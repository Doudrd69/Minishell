#include "../parsing.h"

int	check_arg(int ac)
{
	if (ac < 2)
		return (0);
	return (1);
}

void	parsing(char **env, t_shell *minishell)
{
	minishell->envp = env;
	tokenizers_arg(minishell);
	env += 0;
}

void	tokenizers_arg(t_shell *minishell)
{
	first_parse(minishell, minishell->cmd);
	count_ope(minishell);
	if (minishell->nbr_pipe > 0)
		parse_pipe(minishell, 0, -1);
	if (minishell->nbr_dollars > 0)
		parse_dollars(minishell);
	if (minishell->head && minishell->head != NULL)
		parse_space(minishell);
}

void	first_parse(t_shell *minishell, char *str)
{
	if (ft_strlen(str) > 0)
	{
		minishell->head = ft_dlstnew((void *)str);
		minishell->tail = minishell->head;
		minishell->head->prev = NULL;
		minishell->head->next = NULL;
		minishell->tail->next = NULL;
		minishell->tail->prev = NULL;
		minishell->list_size += 1;
	}
	else
	{
		minishell->head = NULL;
		minishell->tail = NULL;
	}
}
