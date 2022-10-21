#include "../parsing.h"

static void	new_value1(t_shell *minishell, char *str)
{
	int		size;

	size = -1;
	while (str[++size] != '\0' && str[size] != ' ')
		size++;
	minishell->value = (char *)malloc(sizeof(char) * (size + 1));
	size = -1;
	while (str[++size] != '\0' && str[size] != ' ')
		minishell->value[size] = str[size];
	minishell->value[size] = '\0';
}

// static void	newvalue2(t_shell *minishell, char *str)
// {

// }

// static void	newvalue3(t_shell *minishell, char *str)
// {

// }

// static void	newvalue4(t_shell *minishell, char *str)
// {

// }

void	write_newvalue(t_shell *minishell, char *str, int mod)
{
	if (mod == 0)
		new_value1(minishell, str);
	// if (mod == 1)
	// 	new_value2(minishell, str);
	// if (mod == 2)
	// 	new_value3(minishell, str);
	// if (mod == 3)
	// 	new_value4(minishell, str);
	// if (mod == 4)
	// 	new_value5(minishell, str);
}
