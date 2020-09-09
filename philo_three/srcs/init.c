/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrignol <mbrignol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 20:17:06 by mbrignol          #+#    #+#             */
/*   Updated: 2020/09/09 20:17:07 by mbrignol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_three.h"

int		init_struct(char **argv, t_data *data)
{
	data->nb = ft_atoi(argv[0]);
	data->die = ft_atoi(argv[1]);
	data->eat = ft_atoi(argv[2]);
	data->sleep = ft_atoi(argv[3]);
	if (argv[4] != NULL)
		data->must_eat = ft_atoi(argv[4]);
	else
		data->must_eat = 2147483647;
	return (1);
}

int		init_semaphore(t_data *data)
{
	int		i;
	char	*temp;

	i = 0;
	while (i < 200)
	{
		temp = ft_itoa(i);
		sem_unlink(temp);
		free(temp);
		i++;
	}
	sem_unlink("/sem_msg");
	sem_unlink("/take_fork");
	sem_unlink("/sem_fork");
	data->sem_msg = sem_open("/sem_msg", O_CREAT, 0664, 1);
	sem_close(data->sem_msg);
	data->sem_msg = sem_open("/take_fork", O_CREAT, 0664, 1);
	sem_close(data->sem_msg);
	data->sem_fork = sem_open("/sem_fork", O_CREAT, 0664, data->nb);
	sem_close(data->sem_fork);
}

int		init_thinker(t_philo *thinker, t_data *data, int i)
{
	thinker->sem_eat_name = ft_itoa(i);
	thinker->sem_eat = sem_open(thinker->sem_eat_name, O_CREAT, 0664, 1);
	thinker->index = i + 1;
	thinker->data = data;
	thinker->total_meal = 0;
	thinker->is_eating = 0;
	thinker->timeout = data->die;
	thinker->rfork = i;
	thinker->lfork = ((i + 1) == data->nb) ? 0 : (i + 1);
}
