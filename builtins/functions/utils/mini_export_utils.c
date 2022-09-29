#include "../../../includes/minishell.h"

char	**new_tab_malloc(t_mini_data *data, int old_tab_size, char *envp[], char *name, char *value)
{
	int	i;

	i = 0;
	while (i < (old_tab_size + 1))//boucle de malloc des chaines pour les variables de 0 - 36 (=37)
	{
		if (i == old_tab_size - 1)//on a bien itéré 37 fois (old_tab_size + 1) de 0 - 36 et on malloc la var à 35
		{
			data->new_env[i] = malloc(sizeof(char) * (ft_strlen(name) + ft_strlen(value)) + 2);//+2 pour le '=' et le '\0'
			if (!data->new_env[i])
				return (free_tab(data->new_env, i));
			i++;
		}
		else//si j'en suis au dernier on va malloc de i - 1
		{
			if (i == old_tab_size)
			{
				data->new_env[i] = malloc(sizeof(char) * ft_strlen(envp[i - 1]) + 1);
				if (!data->new_env[i])
					return (free_tab(data->new_env, i));
				i++;
			}
			else
			{
				data->new_env[i] = malloc(sizeof(char) * ft_strlen(envp[i]) + 1);
				if (!data->new_env[i])
					return (free_tab(data->new_env, i));
				i++;
			}
		}
	}
	return (data->new_env);
}

char	**new_var_tab_copy(t_mini_data *data, int i, char *name, char *value)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	while (name[j])
	{
		data->new_env[i][j] = name[j];
		j++;
	}
	data->new_env[i][j] = '=';
	j++;
	while (value[k])
	{
		data->new_env[i][j] = value[k];
		k++;
		j++;
	}
	data->new_env[i][j] = '\0';
	return (data->new_env);
}

char	**new_tab_copy(t_mini_data *data, char *envp[], int i, int old_tab_size)
{
	int	j;

	j = 0;
	if (i == old_tab_size)
	{
		while (envp[i - 1][j])
		{
			data->new_env[i][j] = envp[i - 1][j];
			j++;
		}
	}
	else
	{
		while (envp[i][j])
		{
			data->new_env[i][j] = envp[i][j];
			j++;
		}
	}
	data->new_env[i][j] = '\0';
	return (data->new_env);
}