#include "../parsing.h"

static void	new_value1(t_shell *minishell, char *str)
{
	int		size;

	size = 0;
	while (str[size] != '\0' && str[size] != ' ')
		size++;
	minishell->value = (char *)malloc(sizeof(char) * (size + 1));
	size = -1;
	while (str[++size] != '\0' && str[size] != ' ')
		minishell->value[size] = str[size];
	minishell->value[size] = '\0';
}

static void	new_value2(t_shell *minishell, char *str)
{
	int	size;
	int	i;

	size = 0;
	while (str[size] != '\0' && str[size] != ' ')
		size++;
	minishell->value = (char *)malloc(sizeof(char) * (size - 1));
	size = 1;
	i = -1;
	while (str[++size] != '\0' && str[size] != ' ')
	{
		printf("ha =%s, %s\n", minishell->value, str);
		minishell->value[++i] = str[size];
	}
	minishell->value[++i] = '\0';
	printf("VALUE = %s\n", minishell->value);
}

static void	new_value3(t_shell *minishell, char *str, int mod)
{
	int	size;
	int	i;
	int	cpy;

	size = 1;
	i = 0;
	if (mod == 2)
		minishell->value = NULL;
	else
	{
		while (str[i] != '\0' && str[i] != '=')
			i++;
		if (str[i] == '\0')
		{
			minishell->value = NULL;
			return ;
		}
		cpy = i;
		i++;
		while (str[i] != '\0' && str[i] != ' ')
		{
			size++;
			i++;
		}
		i = 0;
		minishell->value = malloc(sizeof(char) * (size + 1));
		while (str[cpy] != '\0' && str[cpy] != ' ')
		{
			minishell->value[i] = str[cpy];
			i++;
			cpy++;
		}
	}
}

static void	new_value4(t_shell *minishell, char *str)
{
	int	size;
	int	i;

	size = 0;
	while (str[size] != '\0' && str[size] != ' ')
		size++;
	minishell->value = (char *)malloc(sizeof(char) * (size));
	size = 0;
	i = 0;
	while (str[++size] != '\0' && str[size] != ' ')
		minishell->value[i++] = str[size];
	minishell->value[size] = '\0';
}

void	write_newvalue(t_shell *minishell, char *str, int mod)
{
	if (mod == 0)
		new_value1(minishell, str);
	if (mod == 1)
		new_value2(minishell, str);
	if (mod == 2 || mod == 5)
		new_value3(minishell, str, mod);
	if (mod == 3)
		new_value4(minishell, str);
}
