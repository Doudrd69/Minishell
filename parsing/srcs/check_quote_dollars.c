#include "minishell.h"

void	check_dquote_dollars(char *str, int *dquote, int i, int *quote)
{
	if (str[i] == '\"' && *dquote != 1)
		*dquote = 1;
	else if (str[i] == '\"' && *dquote != 0)
		*dquote = 0;
	if (str[i] == '\'' && *quote != 1)
		*quote = 1;
	else if (str[i] == '\'' && *quote != 0)
		*quote = 0;
}

int	check_quote_in_quote_dollars(char *str)
{
	int	i;

	i = -1;
	while (str[++i] != '\0')
	{
		if (str[i] == '\"')
		{
			while (str[++i] != '\0' && str[i] != '\"')
			{
				if (str[i] == '\'' && str[i + 1] == '$' && str[i + 2] == '\'')
					return (5);
			}
			return (4);
		}
		if (str[i] == '\'')
			break ;
	}
	return (1);
}

int	check_quote_dollars(char *str)
{
	int	i;
	int	quote;
	int	dquote;

	i = -1;
	quote = 0;
	dquote = 0;
	while (str[++i] != '\0')
	{
		check_dquote_dollars(str, &dquote, i, &quote);
		if (str[i] == '$' && str[i - 1] == '"'
			&& str[i + 1] == '"' && quote != 1)
			return (1);
		if (str[i] == '$' && str[i - 1] == '"' && dquote == 1 && quote != 1)
			return (2);
		if (str[i] == '$' && dquote == 1 && quote != 1)
			return (3);
		if (str[i] == '$' && quote == 1 && dquote != 1)
			return (1);
		if (str[i] == '$' && dquote != 1 && quote != 1)
			return (0);
	}
	return (check_quote_in_quote_dollars(str));
}
