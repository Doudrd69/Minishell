#include "../../../includes/minishell.h"

int check_var_exists_export(t_mini_data *data)
{
	int		i;

	i = 0;
	while (i < data->envp_size)
	{
		if (ft_strnstr(data->env[i], data->name, ft_strlen(data->name)))
		{
			if (check_var(data->env[i], data->name))
			{
				data->var_position = i;
				return (1);
			}
		}
		i++;
	}
	return (0);
}

char	**malloc_tab_with_existing_var(t_mini_data *data)
{
	int	i;

	i = 0;
	while (i < data->envp_size)
	{
		if (i == data->var_position)
		{
			data->new_env[i] = malloc(sizeof(char) * (ft_strlen(data->name) + ft_strlen(data->value) + 2));
			if (!data->new_env[i])
			{
				free_tab(data->new_env, data->envp_size);
				return (0);
			}
		}
		else
		{
			data->new_env[i] = malloc(sizeof(char) * ft_strlen(data->env[i]) + 1);
			if (!data->new_env[i])
			{
				free_tab(data->new_env, data->envp_size);
				return (0);
			}
		}
		//printf("= %d\n", i);
		i++;
	}
	return (data->new_env);
}

char	**copy_value(t_mini_data *data, int i)
{
	int	j;

	j = 0;
	while (data->env[i][j])
	{
		data->new_env[i][j] = data->env[i][j];
		j++;
	}
	data->new_env[i][j] = '\0';
	return (data->new_env);
}

char	**new_tab_with_existing_var(t_mini_data *data)
{
	int	i;

	i = 0;
	data->new_env = malloc(sizeof(char *) * data->envp_size);
	if (!data->new_env)
	{
		free_tab(data->new_env, data->envp_size);
		return (0);
	}
	data->new_env = malloc_tab_with_existing_var(data);//je recup le tableau malloc pour accueillir les copies
	while (i < data->envp_size)
	{
		if (i == data->var_position)
			data->new_env = new_var_tab_copy(data, i, data->name, data->value);
		else
			data->new_env = copy_value(data, i);
		i++;
	}
	return (data->new_env);
}