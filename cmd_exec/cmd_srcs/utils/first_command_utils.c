#include "../../cmd_include/pipex_bonus.h"

int	check_pipe_and_exec(t_data *data)
{
	if (data->exec.pipe_check == 0)
			return (0);
			//first_cmd_execution(data, envp);
	else
	{
		if (dup2(data->pipefd[0][WRITE], STDOUT_FILENO) == -1)//que si pipe ou redirection vers un autre fichier (a ce moment il faudra open avant)
		{
			perror("dup2 == check_pipe_and_exec ==");//celui ci a sauté
			return (1);
		}
	}
	return (0);
}

int	check_inputfile(t_data *data)
{
	if (data->check_hd == 1 && data->exec.infile_check == 0)
	{
		if (dup2(data->hd_pipefd[data->hd_pipe_id - 1][READ], STDIN_FILENO) == -1)
		{
			perror("dup2");
			return (1);
		}
		return (0);
	}
	if (data->exec.infile_check == 1)//on recup du parsing le fichier qui sert d'INFILE
	{
		data->input_fd = open(data->exec.infile_fd, O_RDONLY);//que si infile (si premier noeud de la LC = fichier input + redirection)
		if (data->input_fd < 0)
		{
			ft_printf("minishell: %s: No such file or directory\n", data->exec.infile_fd);
			return (1);
		}
		if (dup2(data->input_fd, STDIN_FILENO) == -1)
		{
			perror("dup2");
			return (1);
		}
		return (0);
	}
	data->input_fd = STDIN_FILENO;
	return (0);
}

int	check_outfile(t_data *data)
{
	if (data->exec.outfile_check == 1)//fonction pour l'ecriture sur fichier de sortie
	{
		if (data->exec.append_check == 1)
			data->output_fd = open(data->exec.outfile_fd, O_WRONLY | O_CREAT, 0666);
		else
		{
			data->output_fd = open(data->exec.outfile_fd, O_WRONLY | O_TRUNC
				| O_CREAT, 0666);
		}
		if (data->output_fd < 0)
		{
			ft_printf("Error : can't open file :\n");//afficher le bon fichier
			return (1);
		}
		if (dup2(data->output_fd, STDOUT_FILENO) == -1)
		{
			perror("dup2");
			return (1);
		}
		return (0);
	}
	else
		return (check_pipe_and_exec(data));
}
