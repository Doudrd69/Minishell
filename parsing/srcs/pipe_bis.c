#include "../parsing.h"

static void	check_syntax(t_shell *minishell, char *str, int i)
{
	int	j;

	minishell += 0;
	j = i;
	if (str[i + 1] == '|')
	{
		printf("minishell: syntax error near unexpected token `||'\n");
		exit(0);
	}
	if (i == 0 || str[i + 1] == '\0')
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		exit(0);
	}
	while (--j >= 0 && str[j] == ' ')
	{
		if (j == 0)
		{
			printf("minishell: syntax error near unexpected token `|'\n");
			exit(0);
		}
	}
	while (str[++i] != '\0' && (str[i] == ' ' || str[i] == '|'))
	{
		if (str[i] == '|')
		{
			if (str[i + 1] == '|')
				printf("minishell: syntax error near unexpected token `||'\n");
			else
				printf("minishell: syntax error near unexpected token `|'\n");
			exit(0);
		}
	}
}

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
	int		i;
	char	*tmp;

	i = 0;
	tmp = str;
	str = str + len;
	while (i < len + 1 && str[i] + len != '\0')
	{
		if ((str[i]) == '\"' && minishell->quote != 1
			&& str[i - 1] != '\\')
			minishell->quote = 1;
		else if (str[i] == '\"' && minishell->quote != 0 && str[i - 1] != '\\')
			minishell->quote = 0;
		if (str[i] == '|' && minishell->quote == 1)
		{
			return (1);
		}
		if (str[i] == '|' && minishell->quote == 0)
		{
			check_syntax(minishell, tmp, len);
			(*pipe)--;
			return (0);
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
