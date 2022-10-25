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

static void	new_value3(t_shell *minishell)
{
	minishell->value = NULL;
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
		new_value3(minishell);
	if (mod == 3)
		new_value4(minishell, str);
}
