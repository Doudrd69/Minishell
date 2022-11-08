#include "../parsing.h"

static void	count_lenght_ws(char const *str, int *wlen, int *i)
{
	while (str[*i] != ' ' && str[*i])
	{
		if (str[*i] == '\'')
		{
			(*i) += 1;
			while (str[*i] != '\0' && str[*i] != '\'')
			{
				(*i) += 1;
				(*wlen) += 1;
			}
		}
		if (str[*i] == '\"')
		{
			(*i) += 1;
			while (str[*i] != '\0' && str[*i] != '\"')
			{
				(*i) += 1;
				(*wlen) += 1;
			}
		}
		if ((str[*i] == '\"' || str[*i] == '\'') && str[*i] != '\0')
			(*i) += 1;
		if (str[*i] != '\0' && str[*i] != ' ')
		{
			(*i) += 1;
			(*wlen) += 1;
		}
	}
}

int	ft_split_minishell_malloc_ws(char const	*str, char charset, char **tab)
{
	int	i;
	int	wlen;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		wlen = 0;
		while (str[i] == ' ' && str[i])
			i++;
		count_lenght_ws(str, &wlen, &i);
		tab[j] = (char *)malloc(sizeof(char) * (wlen + 1));
		if (tab[j] == NULL)
			return (j);
		if (str[i] == charset || str[i] == '\0')
			j++;
		while (str[i] == charset && str[i])
			i++;
	}
	return (0);
}
