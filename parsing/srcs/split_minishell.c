#include "../parsing.h"

int	p_status;

static char	**ft_free(int k, char **tab)
{
	while (k > 0)
	{
		free(tab[k]);
		k--;
	}
	free(tab);
	return (NULL);
}

static int	fill_with_quotes(char const *str, int *i, int *k, char ***tab)
{
	int	x;
	int	j;

	x = 0;
	while (str[*i] != ' ' && str[*i] != '\0')
	{
		if (str[*i] == '\'')
		{
			if (str[*i + 1] == '\0')
				(*tab)[*k][x++] = str[*i];
			(*i) += 1;
			while (str[*i] != '\0' && str[*i] != '\'')
			{
				(*tab)[*k][x++] = str[*i];
				(*i) += 1;
			}
			if (str[*i] == '\'' && str[*i] != '\0')
				(*i) += 1;
			if (str[*i] == ' ')
			{
				j = (*i);
				while (str[j] != '\0')
				{
					if (str[j] != ' ')
					{
						(*tab)[*k][x++] = ' ';
						(*i) = j;
						break ;
					}
					j++;
				}
			}
		}
		if (str[*i] == '\"')
		{
			if (str[*i + 1] == '\0')
				(*tab)[*k][x++] = str[*i];
			(*i) += 1;
			while (str[*i] != '\0' && str[*i] != '\"')
			{
				(*tab)[*k][x++] = str[*i];
				(*i) += 1;
			}
			if (str[*i] == '\"' && str[*i] != '\0')
				(*i) += 1;
			if (str[*i] == ' ')
			{
				j = (*i);
				while (str[j] != '\0')
				{
					if (str[j] != ' ')
					{
						(*tab)[*k][x++] = ' ';
						(*i) = j;
						break ;
					}
					j++;
				}
			}
		}
		if (str[*i] != '\0' && str[*i] != ' ' && str[*i] != '\"' && str[*i] != '\'')
		{
			(*tab)[*k][x++] = str[*i];
			(*i) += 1;
		}
	}
	if (x != 0)
		(*tab)[*k][x] = '\0';
	return (x);
}

char	**ft_split_minishell_get_filling(char const *str, char **tab)
{
	int	i;
	int	k;
	int	x;

	i = 0;
	k = 0;
	while (str[i])
	{
		while (str[i] == ' ' && str[i])
			i++;
		x = fill_with_quotes(str, &i, &k, &tab);
		if ((str[i] == ' ' || str[i - x] != '\0') && x != 0)
			k++;
		while (str[i] == ' ' && str[i])
			i++;
	}
	return (tab);
}

char	**ft_split_minishell(t_shell *minishell, char const *str, char c)
{
	char	**tab;
	int		nbrw;

	if (!str)
		return (NULL);
	nbrw = ft_nbr_words_split_minishell(minishell, str, c);
	if (nbrw == 0)
	{
		if (strlen(str) == 2)
		{
			printf("minishell: : command not found\n");
			p_status = 127;
		}
		return (NULL);
	}
	tab = (char **)malloc(sizeof(char *) * (nbrw + 1));
	if (tab == NULL)
		return (NULL);
	tab[nbrw] = 0;
	if (ft_split_minishell_malloc_ws(str, c, tab))
		return (ft_free(ft_split_minishell_malloc_ws(str, c, tab), tab));
	tab = ft_split_minishell_get_filling(str, tab);
	return (tab);
}
