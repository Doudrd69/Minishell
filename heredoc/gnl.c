#include "../includes/minishell.h"

size_t	ft_strlen_gnl(char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

size_t	ft_strnlen(char *s)
{
	int	i;

	i = 0;
	while (s[i] && (s[i] != '\n'))
		i++;
	if (s[i] == '\n')
		i++;
	return (i);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	int	i;
	int	j;
	char	*tab;

	i = 0;
	j = 0;
	tab = malloc(sizeof(char) * (ft_strlen_gnl(s1) + ft_strnlen(s2) + 1));
	if (tab)
	{
		while (s1 && s1[i])
		{
			tab[i] = s1[i];
			i++;
		}
		while (s2[j] && (s2[j] != '\n'))
			tab[i++] = s2[j++];
		if (s2[j] == '\n')
			tab[i] = '\n';
		if (s2[j] == '\n')
			i++;
		tab[i] = '\0';
	}
	free(s1);
	return (tab);
}

void	newline_separator(char *s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i] && (s[i] != '\n'))
		i++;
	if (s && (s[i] == '\n'))
		i++;
	while (j < BUFFER_SIZE - i)
	{
		s[j] = s[i + j];
		j++;
	}
	s[j] = '\0';
}

int	check_newline(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			return (0);
		i++;
	}
	return (1);
}

char	*buffer_separator(char *buffer, char *line)
{
	if (!check_newline(buffer))
	{	
		newline_separator(buffer);
		line = ft_strjoin_gnl(line, buffer);
		if (line && line[0] == '\0')
		{
			free(line);
			return (NULL);
		}
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	int			index;
	char		*line;

	index = 1;
	line = NULL;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	line = buffer_separator(buffer, line);
	while (index > 0 && check_newline(buffer))
	{
		index = read(fd, buffer, BUFFER_SIZE);//return -1
		if (index <= 0)
			return (NULL);
		buffer[index] = '\0';
		line = ft_strjoin_gnl(line, buffer);
		if (!line)
			return (NULL);
	}
	return (line);
}
