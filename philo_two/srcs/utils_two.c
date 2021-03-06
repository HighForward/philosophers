/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrignol <mbrignol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 18:42:27 by mbrignol          #+#    #+#             */
/*   Updated: 2020/09/26 03:32:02 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_two.h"

static int	ft_itoamalloc(int nb)
{
	int xd;

	xd = 0;
	xd = (nb <= 0 ? 1 : 0);
	while (nb != 0)
	{
		nb = nb / 10;
		xd++;
	}
	return (xd);
}

char		*ft_itoa(int n)
{
	char			*str;
	int				len;
	int				less;
	unsigned int	nb;

	str = NULL;
	less = (n < 0 ? 1 : 0);
	len = ft_itoamalloc(n);
	if (!(str = (char*)malloc(sizeof(char) * len + 1)))
		return (NULL);
	str[len--] = '\0';
	nb = (n < 0 ? -n : n);
	while (len >= 0)
	{
		str[len] = nb % 10 + 48;
		nb = nb / 10;
		len--;
	}
	if (less == 1)
		str[0] = '-';
	return (str);
}

long int	current_time(t_data data)
{
	struct timeval current;

	gettimeofday(&current, NULL);
	return ((current.tv_usec - data.start.tv_usec) / 1000
			+ (current.tv_sec - data.start.tv_sec) * 1000);
}

int			return_str(char *str, int ret)
{
	ft_putstr(str);
	return (ret);
}

void		ft_usleep(int n)
{
	struct timeval start;
	struct timeval step;

	gettimeofday(&start, NULL);
	while (1)
	{
		usleep(50);
		gettimeofday(&step, NULL);
		if ((step.tv_sec - start.tv_sec) * 1000000 +
			(step.tv_usec - start.tv_usec) > n)
			break ;
	}
}
