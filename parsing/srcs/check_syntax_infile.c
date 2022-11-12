#include "../parsing.h"

int	p_status;

static int	check_syntax_after_space(t_shell *minishell, char *str, int i)
{
	int	j;

	j = 0;
	minishell += 0;
	i++;
	while (str[i] != '\0' && str[i] == ' ')
		i++;
	j = ft_strlen(str);
	if (j == i)
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		p_status = 258;
		exit (0);
	}
	if (j >= i + 3)
	{
		if (str[i] == '<' && str[i + 1] == '<' && str[i + 2] == '<')
		{
			printf("minishell: syntax error near unexpected token `<<<'\n");
			p_status = 258;
			exit (0);
		}
	}
	if (j >= i + 2)
	{
		if (str[i] == '<' && str[i + 1] == '<')
		{
			printf("minishell: syntax error near unexpected token `<<'\n");
			p_status = 258;
			exit (0);
		}
		if (str[i] == '>' && str[i + 1] == '>')
		{
			printf("minishell: syntax error near unexpected token `>>'\n");
			p_status = 258;
			exit (0);
		}
		if (str[i] == '>' && str[i + 1] == '|')
		{
			printf("minishell: syntax error near unexpected token `>|'\n");
			p_status = 258;
			exit (0);
		}
		if (str[i] == '|' && str[i + 1] == '|')
		{
			printf("minishell: syntax error near unexpected token `||'\n");
			p_status = 258;
			exit (0);
		}
	}
	if (j >= i + 1)
	{
		if (str[i] == '<')
		{
			printf("minishell: syntax error near unexpected token `<'\n");
			p_status = 258;
			exit (0);
		}
		if (str[i] == '>')
		{
			printf("minishell: syntax error near unexpected token `>'\n");
			p_status = 258;
			exit (0);
		}
		if (str[i] == '|')
		{
			printf("minishell: syntax error near unexpected token `|'\n");
			p_status = 258;
			exit (0);
		}
	}
	return (1);
}

int	check_syntax_infile(t_shell *minishell, char *str, int i)
{
	int	j;

	j = ft_strlen(str);
	if (j == i)
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		p_status = 258;
		exit (0);
	}
	if (j >= i + 2)
	{
		if (str[i + 1] == '|' && str[i + 2] == '|')
		{
			printf("minishell: syntax error near unexpected token `||'\n");
			p_status = 258;
			exit (0);
		}
		if (str[i + 1] == '>' && str[i + 2] == '>' && str[i + 3] == '>')
		{
			printf("minishell: syntax error near unexpected token `>>'\n");
			p_status = 258;
			exit (0);
		}
		else if (str[i + 1] == '>' && str[i + 2] == '>')
		{
			printf("minishell: syntax error near unexpected token `>'\n");
			p_status = 258;
			exit (0);
		}
	}
	if (j >= i + 1)
	{
		if (str[i + 1] == '|')
		{
			printf("minishell: syntax error near unexpected token `|'\n");
			p_status = 258;
			exit (0);
		}
	}
	check_syntax_after_space(minishell, str, i);
	return (1);
}
