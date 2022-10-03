#include "../includes/minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (((unsigned char)s1[i]) - ((unsigned char)s2[i]));
}

int	ft_strncmp(const char *s1, const char *s2, size_t size)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < (size - 1))
		i++;
	return (((unsigned char)s1[i]) - ((unsigned char)s2[i]));
}

int	ft_strlcpy(char *dst, const char *src, size_t size, int check)
{
	size_t	i;
	size_t	src_lenght;

	i = 0;
	src_lenght = 0;
	while (src[src_lenght])
		src_lenght++;
	if (size == 0)
		return (src_lenght);
	while (src[i] && i < size)
	{
		dst[i] = src[i];
		i++;
	}
	if (check == 1)
		dst[i] = '\0';
	return (src_lenght);
}
