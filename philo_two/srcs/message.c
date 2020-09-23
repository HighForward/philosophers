/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrignol <mbrignol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 18:37:12 by mbrignol          #+#    #+#             */
/*   Updated: 2020/09/23 04:35:28 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_two.h"

int	message_alert(long int time, int index, t_philo *thinker, int status)
{
	sem_wait(thinker->data->sem_msg);
	if (thinker->data->stop == 1)
		return (0);
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
	if (status != DIED && status != FED)
		sem_post(thinker->data->sem_msg);
	return (1);
}
