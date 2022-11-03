#include "../parsing.h"

static int	count_word(char const *str, char charset, int *i, int *nbrw)
{
	while (str[*i] == charset && str[*i])
	{
		(*i) += 1;
	}
	if (str[*i] != charset && str[*i])
		(*nbrw) += 1;
	while (str[*i] != charset && str[*i])
	{
		if (str[*i] == '\'')
			return (1);
		if (str[*i] == '\"')
			return (2);
		(*i) += 1;
	}
	return (0);
}

static void	pass_quote(char const *str, char charset, int *i)
{
	if (str[(*i) + 1] == '\0')
		return ;
	(*i) += 1;
	while (str[*i] != '\0' && str[*i] != '\'')
		(*i) += 1;
	if (str[*i] != '\0')
	{
		while (str[*i] != '\0' && str[*i] != charset)
			(*i) += 1;
	}
}

static void	pass_dquote(char const *str, char charset, int *i)
{
	if (str[(*i) + 1] == '\0')
		return ;
	(*i) += 1;
	while (str[*i] != '\0' && str[*i] != '\"')
		(*i) += 1;
	if (str[*i] != '\0')
	{
		while (str[*i] != '\0' && str[*i] != charset)
			(*i) += 1;
	}
}

int	ft_nbr_words_split_minishell(t_shell *minishell,
	char const	*str, char charset)
{
	int	nbrw;
	int	i;

	nbrw = 0;
	i = 0;
	while (str[i])
	{
		minishell->mod = count_word(str, charset, &i, &nbrw);
		if (minishell->mod == 1)
			pass_quote(str, charset, &i);
		if (minishell->mod == 2)
			pass_dquote(str, charset, &i);
	}
	printf("nbr word = %d\n", nbrw);
	return (nbrw);
}
