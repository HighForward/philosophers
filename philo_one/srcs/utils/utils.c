#include "../../includes/philo_one.h"

int	ft_strlen(const char *str)
{
	int i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		i++;
	}
	return (i);
}

void	ft_putstr(char *str)
{
	int i;
	int size;

	i = 0;
	size = ft_strlen(str);
	while (i < size)
	{
		write(1, &str[i], 1);
		i++;
	}
}

int	ft_atoi(const char *nptr)
{
	unsigned int		i;
	unsigned long int	nb;
	unsigned long int	less;

	less = 1;
	i = 0;
	nb = 0;
	while ((nptr[i] == '\t' || nptr[i] == '\n' || nptr[i] == '\v' ||
			nptr[i] == '\f' || nptr[i] == '\r' || nptr[i] == ' '))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			less = -1;
		i++;
	}
	while (nptr[i] && nptr[i] >= '0' && nptr[i] <= '9')
		nb = nb * 10 + (unsigned long int)(nptr[i++] - 48);
	if (nb > 9223372036854775807 && less == (unsigned long int)-1)
		return (0);
	else if (nb > 9223372036854775807)
		return (-1);
	return (nb * less);
}