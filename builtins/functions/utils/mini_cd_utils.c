#include "../../../includes/minishell.h"

int find_pwd(t_mini_data *data)
{
	int	i;

	i = 0;
	while (i < data->envp_size)
	{
		if (ft_strnstr(data->env[i], "PWD", ft_strlen("PWD")))
		{
			if (check_var(data->env[i], "PWD"))
				return (i);
		}
		i++;
	}
	return (i);
}

int	update_pwd(t_mini_data *data)
{
	int		position;
	int		size;
	char	*str;
	char	*cwd;

	position = find_pwd(data);
	if (position == data->envp_size)
		return (1);
	cwd = getcwd(data->buff, BUF_SIZE);
	size = ft_strlen(cwd);//taille de VALUE
	str = malloc(sizeof(char) * size + 5);//5 pour PWD= et le \0
	if (!str)
		return (1);
	ft_strlcpy(str, "PWD=", 5, 0);
	ft_strlcpy(&str[4], cwd, ft_strlen(cwd), 1);
	ft_strlcpy(data->env[position], str, ft_strlen(str), 1);
	free(str);
	return (0);
}