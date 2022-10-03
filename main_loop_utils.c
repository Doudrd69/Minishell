#include "includes/minishell.h"
#include "cmd_exec/cmd_include/pipex_bonus.h"

int export_exec(t_mini_data *mini_data, t_data *data)
{
	mini_data->new_env_check = 1;
	if (mini_data->unset_env && mini_data->unset_env_check == 1)
	{
		free_tab(mini_data->unset_env, mini_data->envp_size - 2);
		mini_data->unset_env_check = 0;
	}
	mini_data->env = mini_data->new_env;
	data->envp = mini_data->new_env;
	return (0);
}

int	unset_exec(t_mini_data *mini_data, t_data *data)
{
	mini_data->unset_env_check = 1;
	if (mini_data->new_env)
	{
		free_tab(mini_data->new_env, mini_data->envp_size);
		mini_data->new_env_check = 0;
	}
	mini_data->env = mini_data->unset_env;
	data->envp = mini_data->unset_env;
	return (0);
}
