#include "../parsing.h"

int	p_status;

static void	check_syntax(t_shell *minishell, char *str, int i)
{
	int	j;

	minishell += 0;
	if (i != 0)
		i++;
	j = i;
	if (str[i + 1] == '|')
	{
		printf("minishell: syntax error near unexpected token `||'\n");
		p_status = 258;
		exit(0);
	}
	if (i == 0 || str[i + 1] == '\0')
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		p_status = 258;
		exit(0);
	}
	while (--j >= 0 && str[j] == ' ')
	{
		if (j == 0)
		{
			printf("minishell: syntax error near unexpected token `|'\n");
			p_status = 258;
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
			p_status = 258;
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
	if (len == -1)
		len = 0;
	tmp = str;
	str = str + (len);
	minishell->dquote = 0;
	minishell->quote = 0;
	while (str[i] != '\0')
	{
		if ((str[i]) == '\"' && minishell->dquote != 1)
			minishell->dquote = 1;
		else if (str[i] == '\"' && minishell->dquote != 0)
			minishell->dquote = 0;
		if (str[i] == '\'' && minishell->quote != 1)
			minishell->quote = 1;
		else if (str[i] == '\'' && minishell->quote != 0)
			minishell->quote = 0;
		if (str[i] == '|' && (minishell->dquote == 1 || minishell->quote == 1))
		{
			return (1);
		}
		if (str[i] == '|' && minishell->dquote == 0 && minishell->quote == 0)
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
