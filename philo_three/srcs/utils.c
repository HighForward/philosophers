#include "../includes/philo_three.h"

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

void	ft_putchar(char c)
{
    write(1, &c, 1);
}

void	ft_putnbr(int nb)
{
    int nbr;

    if (nb == -2147483648)
    {
        write(1, "-2147483648", 11);
        return ;
    }
    if (nb < 0)
    {
        nbr = nb * -1;
        write(1, "-", 1);
    }
    else
        nbr = nb;
    if (nbr >= 10)
    {
        ft_putnbr(nbr / 10);
    }
    ft_putchar(nbr % 10 + 48);
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

long int current_time(t_data data)
{
    struct timeval current;

    gettimeofday(&current, NULL);
    return ((current.tv_usec - data.start.tv_usec) / 1000
            + (current.tv_sec - data.start.tv_sec) * 1000);
}

int return_str(char *str, int ret)
{
    ft_putstr(str);
    return (ret);
}