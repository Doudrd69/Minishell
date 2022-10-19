#include "../parsing.h"

void	parse_quote(char *str, t_shell *minishell)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\"')
		{
			printf("double quote\n");
			str = ft_copy_string_without_quote(str, '"');
			ft_dlstadd_back((&(minishell)),
				ft_dlstnew((void *)str));
		}
		i++;
	}
}

char	*ft_copy_string_without_quote(char *str, char quote)
{
	int		i;
	int		j;
	char	*newstr;

	j = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == quote)
			j++;
		i++;
	}
	newstr = malloc(sizeof(char) * (i - j + 1));
	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] != quote)
			newstr[j++] = str[i];
		i++;
	}
	newstr[j] = '\0';
	printf("newstr = %s\n", newstr);
	return (newstr);
}
