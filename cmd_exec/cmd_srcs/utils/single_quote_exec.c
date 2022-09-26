#include "../../cmd_include/pipex_bonus.h"

int	check_sq_cmd(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == ' ')
			return (1);
		i++;
	}
	return (0);
}