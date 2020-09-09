/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 04:35:45 by user42            #+#    #+#             */
/*   Updated: 2020/09/09 04:35:46 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

void	message_alert(long int time, int index, t_philo *thinker, int status)
{
	pthread_mutex_lock(&thinker->data->mutex_msg);
	ft_putnbr(time);
	ft_putchar(' ');
	if (status != FED)
	{
		ft_putnbr(index);
		ft_putchar(' ');
	}
	if (status == EAT)
		write(1, "is eating\n", 10);
	else if (status == SLEEP)
		write(1, "is sleeping\n", 12);
	else if (status == THINK)
		write(1, "is thinking\n", 12);
	else if (status == FORK)
		write(1, "has taken a fork\n", 17);
	else if (status == DIED)
		write(1, "died\n", 5);
	else if (status == FED)
		write(1, "everyone is fed\n", 16);
	if (status != DIED)
		pthread_mutex_unlock(&thinker->data->mutex_msg);
}
