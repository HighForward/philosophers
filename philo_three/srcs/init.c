/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrignol <mbrignol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 20:17:06 by mbrignol          #+#    #+#             */
/*   Updated: 2020/09/26 09:05:37 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_three.h"

void	unlink_semaphore(void)
{
	sem_unlink("/sem_msg");
	sem_unlink("/take_fork");
	sem_unlink("/sem_fork");
	sem_unlink("/stop");
	sem_unlink("/death");
}

int		init_semaphore(t_data *data)
{
	unlink_semaphore();
	if ((data->sem_msg = sem_open("/sem_msg", O_CREAT, 0664, 1)) == SEM_FAILED)
		return (return_str("SEM_OPEN_ERROR\n", 1));
	if ((data->take_fork = sem_open("/take_fork", O_CREAT, 0664, 1)) == SEM_FAILED)
		return (return_str("SEM_OPEN_ERROR\n", 1));
	if ((data->sem_fork = sem_open("/sem_fork", O_CREAT, 0664, data->nb)) == SEM_FAILED)
		return (return_str("SEM_OPEN_ERROR\n", 1));
	if ((data->stop = sem_open("/stop", O_CREAT, 0664, 1)) == SEM_FAILED)
		return (return_str("SEM_OPEN_ERROR\n", 1));
	if ((data->death = sem_open("/death", O_CREAT, 0664, 1)) == SEM_FAILED)
		return (return_str("SEM_OPEN_ERROR\n", 1));

	sem_wait(data->stop);
	sem_wait(data->death);
//	return (0);
}

int		init_thinker(t_philo *t, t_data *data, int i)
{
//	thinker->sem_eat_name = ft_itoa(i);
//	thinker->sem_eat = sem_open(thinker->sem_eat_name, O_CREAT, 0664, 1);
	t->index = i;
	t->data = data;
	t->total_meal = 0;
	t->is_eating = 0;
	t->timeout = data->die;
	t->leave_thread = 0;
	return (0);
}
