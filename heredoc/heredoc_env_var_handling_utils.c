#include "../cmd_exec/cmd_include/pipex_bonus.h"

int	check_special_char(char c, int size)
{
	if (c == '$' && size != 0)
		return (1);
	if (c == '"' && size != 0)
		return (1);
	if (c == '\'' && size != 0)
		return (1);
	if (c == '\\' && size != 0)
		return (1);
	return (0);
}

int	check_special_char_second_loop(char c)
{
	if (c == '\0')
		return (1);
	if (c == '"' || c == '\'')
		return (1);
	if (c == '\\')
		return (1);
	return (0);
}

int	backslash_check(t_data *data, char *str, int i)
{
	if (str[i] == '\\' && str[i + 1] == '$')
	{
		data->hd.bkslash_check = 1;
		i++;
	}
	if (str[i] == '\\' && str[i + 1] == '\\')
		i++;
	return (i);
}