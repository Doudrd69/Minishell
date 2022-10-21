#include "minishell.h"

int	var_exists(t_shell *minishell)
{
	int	i;

	i = 0;
	while (minishell->envp[i])
	{
		if (ft_strnstr(minishell->envp[i], minishell->var_search,
				ft_strlen(minishell->var_search)))
		{
			if (check_var(minishell->envp[i], minishell->var_search))
				return (1);
		}
		i++;
	}
	return (0);
}

int	check_var(char *str, char *var_name)
{
	size_t	size;

	size = 0;
	while (str[size] != '=')
		size++;
	if (size == ft_strlen(var_name))
		return (1);
	return (0);
}
