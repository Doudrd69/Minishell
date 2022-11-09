#include "../parsing.h"

static int	check_dollars_mod(char *str)
{
	int	mod;
	int	i;

	i = 0;
	mod = 0;
	if (str[i + 1] != '\0' && ((str[i + 1] == 34 && str[i - 1] != 34) || (str[i + 1] == 39 && str[i - 1] != 39)))
		mod = 3;
	if (str[i + 1] != '\0' && (str[i + 1] == 36
			|| (str[i + 1] >= 48 && str[i + 1] <= 57) || str[i + 1] == 42
			|| str[i + 1] == 64 || str[i + 1] == 92))
	{
		mod = 1;
	}
	if (str[i + 1] != '\0' && ((str[i + 1] >= 65 && str[i + 1] <= 90)
			|| str[i + 1] == 95 || (str[i + 1] >= 97 && str[i + 1] <= 122)))
	{
		mod = 2;
	}
	return (mod);
}

void	parse_dollars(t_shell *minishell)
{
	int		i;
	t_node	*list_cpy;
	char	*str;
	int		dollars;

	dollars = minishell->nbr_dollars;
	list_cpy = minishell->head;
	while (list_cpy && list_cpy != NULL)
	{
		i = 0;
		str = (char *)(list_cpy->content);
		while (str && str[i] != '\0')
		{
			if (str[i] == '$')
			{
				dollars--;
				minishell->mod = check_quote_dollars(str);
				printf("%s\n", (char *)(list_cpy->content));
				dollars_mod(str, i, minishell, &list_cpy);
				str = (char *)(list_cpy->content);
			}
			i++;
		}
		if (list_cpy != NULL)
			list_cpy = list_cpy->next;
	}
}

static int	check_dollar_export(char *str, int i)
{
	if (i == 0 || str[i - 1] == ' ')
		return (2);
	while (i > 0 && str[i] != ' ')
		i--;
	if (i > 3)
		i--;
	else
		return (2);
	while (i > 0 && str[i] != ' ')
	{
		i--;
	}
	if (ft_strncmp(str, "export", 6) != 0)
		return (2);
	return (5);
}

char	*dollars_mod(char *str, int i, t_shell *minishell, t_node **list)
{
	int	check;

	if (minishell->mod == 0 || minishell->mod == 2
		|| minishell->mod == 4 || minishell->mod == 3)
	{
		check_and_print_var_parsing(minishell, str + i);
		if (minishell->value)
		{
			change_var_to_value(str, i, minishell, list);
		}
		else
		{
			check = check_dollars_mod(str + i);
			if (check == 2)
				check = check_dollar_export(str, i);
			write_newvalue(minishell, str + i, check);
			change_var_to_value(str, i, minishell, list);
		}
	}
	else
	{
		check = check_dollars_mod(str + i);
		write_newvalue(minishell, str + i, check);
		change_var_to_value(str, i, minishell, list);
	}
	return (str);
}

void	change_var_to_value(char *str, int i, t_shell *minishell, t_node **list)
{
	char	*tmp;
	char	*cpy;
	int		size;
	int		j;
	int		k;

	size = 0;
	j = 0;
	cpy = &str[i];
	while (cpy[++size] != '\0' && cpy[size] != ' ' && cpy[size] != '$')
		if (cpy[size] == '\"' || cpy[size] == '\'')
			j++;
	tmp = (char *)malloc(sizeof(char)
			* (ft_strlen(minishell->value) + j - size + ft_strlen(str) + 1));
	j = -1;
	k = 0;
	while (++j < i)
		tmp[j] = str[k++];
	size += k;
	replace_value_and_after(minishell, &j, &tmp);
	while (str[size] && str[size] != '\0')
	{
		tmp[j++] = str[size++];
	}
	tmp = replace_quote_dollars(minishell, tmp, j);
	include_dollar_list(minishell, list, tmp);
}

void	replace_value_and_after(t_shell *minishell, int *j, char **tmp)
{
	int	k;

	k = 0;
	while (minishell->value && minishell->value[k] != '\0')
		(*tmp)[(*j)++] = minishell->value[k++];
}
