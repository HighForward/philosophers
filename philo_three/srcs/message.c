/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrignol <mbrignol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 20:17:36 by mbrignol          #+#    #+#             */
/*   Updated: 2020/09/26 03:31:16 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_three.h"

void	message_alert(long int time, int index, t_philo *thinker, int status)
{
	sem_wait(thinker->data->sem_msg);
	ft_putnbr(time);
	ft_putchar(' ');
	ft_putnbr(index);
	ft_putchar(' ');
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
	if (status != DIED)
		sem_post(thinker->data->sem_msg);
}
