#include "../parsing.h"

int	check_and_print_var(t_shell *minishell, char *str)
{
	int		size;
	int		i;
	int		j;
	char	*position;

	j = 0;
	size = 0;
	i = 0;
	position = &str[0];
	find_position_of_dollars(position, i, &size);
	i = 1;
	minishell->var_search = malloc(sizeof(char) * size);
	if (!(minishell->var_search))
		return (1);
	while (i < size)
	{
		if (str[i] == '$' && i != 0)
			break ;
		minishell->var_search[j] = str[i];
		i++;
		j++;
	}
	minishell->var_search[j] = '\0';
	print_var_parsing(minishell);
	return (0);
}

void	find_position_of_dollars(char *position, int i, int *size)
{
	while (position[*size] != '\0' && position[*size] != ' ')
	{
		if (position[*size] == '$' && *size != 0)
			break ;
		if (position[*size] == '\"' || position[*size] == '\'')
			i++;
		(*size)++;
	}
	*size -= i;
}

static void	ft_find_dollars(t_shell *minishell, char *var, int *size, int *i)
{
	char	*position;

	position = &minishell->var_search[0];
	while (position[*size] != '\0' && position[*size] != ' '
		&& position[*size] != '\"')
	{
		if (position[*size] == '$' && *size != 0)
			break ;
		(*size)++;
	}
	while (var[*i] != ' ' && var[*i] != '\0')
		(*i)++;
}

void	print_var_parsing(t_shell *minishell)
{
	int		size;
	int		i;
	int		j;
	char	*var;

	size = 0;
	i = 0;
	if (var_exists(minishell))
	{
		var = getenv(minishell->var_search);
		ft_find_dollars(minishell, var, &size, &i);
		minishell->value = malloc(sizeof(char) * (i + 1));
		if (!(minishell->value))
			return ;
		j = 0;
		while (var[j] != ' ' && var[j] != '\0')
		{
			minishell->value[j] = var[j];
			j++;
		}
		minishell->value[i] = '\0';
	}
	return ;
}
