/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 04:40:31 by user42            #+#    #+#             */
/*   Updated: 2020/09/22 23:16:54 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

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
