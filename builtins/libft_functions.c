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

char	*recursive_conversion(long int nbr, char *tab, int length)
{
	if (nbr >= 10)
		recursive_conversion(nbr / 10, tab, length - 1);
	tab[length - 1] = (nbr % 10 + 48);
	return (tab);
}

int	digit_count(long int n)
{
	int	i;

	i = 0;
	if (n < 0)
	{
		n *= -1;
		i++;
	}
	while (n >= 10)
	{
		n /= 10;
		i++;
	}
	return (i + 1);
}

char	*ft_itoa(int n)
{
	int			i;
	long int	nb;
	char		*tab;

	nb = n;
	i = digit_count(n);
	tab = malloc(sizeof(char) * (i + 1));
	if (!tab)
		return (NULL);
	if (nb < 0)
	{
		tab[0] = '-';
		nb *= -1;
	}
	tab[i] = 0;
	recursive_conversion(nb, tab, i);
	return (tab);
}