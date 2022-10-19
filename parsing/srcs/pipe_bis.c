#include "../parsing.h"

char	*cmd_cpy(char *dest, char *src, int size)
{
	int	i;

	if (size == 0)
		return (NULL);
	i = -1;
	dest[1] = src[1];
	while (src[++i] && i < size - 1)
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}

int	check_quote_pipe(t_shell *minishell, char *str, int len, int *pipe)
{
	int	i;

	i = 0;
	while (i < len + 1 && str[i] != '\0')
	{
		if (str[i] == '\"' && minishell->quote != 1 && str[i - 1] != '\\')
			minishell->quote = 1;
		else if (str[i] == '\"' && minishell->quote != 0 && str[i - 1] != '\\')
			minishell->quote = 0;
		if (str[i] == '|' && minishell->quote == 1)
			return (0);
		if (str[i] == '|' && minishell->quote == 0)
		{
			(*pipe)--;
			return (1);
		}
		i++;
	}
	return (1);
}

void	ft_incr_var_pipe(int *j, int *i)
{
	*(j) += (*(i));
	*(i) = 0;
}
