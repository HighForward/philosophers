/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrignol <mbrignol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 20:17:06 by mbrignol          #+#    #+#             */
/*   Updated: 2020/09/23 07:57:48 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_three.h"

int		check_input(char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int		init_struct(char **argv, t_data *data)
{
	if (check_input(argv) == 0)
		return (0);
	data->nb = ft_atoi(argv[0]);
	if (data->nb < 2 || data->nb > 200)
		return (return_str("must be > 2 || < 200\n", 0));
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
	sem_unlink("/stop");
	sem_unlink("/fed");
	data->sem_msg = sem_open("/sem_msg", O_CREAT, 0664, 1);
	sem_close(data->sem_msg);
	data->sem_msg = sem_open("/take_fork", O_CREAT, 0664, 1);
	sem_close(data->sem_msg);
	data->sem_fork = sem_open("/sem_fork", O_CREAT, 0664, data->nb);
	sem_close(data->sem_fork);
	data->stop = sem_open("/stop", O_CREAT, 0664, 1);
	data->fed = sem_open("/fed", O_CREAT, 0664, 1);
	sem_post(data->stop);
//	sem_post(data->fed);
	return (0);
}

int		init_thinker(t_philo *thinker, t_data *data, int i)
{
	thinker->stop = 0;
	thinker->sem_eat_name = ft_itoa(i);
	thinker->sem_eat = sem_open(thinker->sem_eat_name, O_CREAT, 0664, 1);
	thinker->index = i + 1;
	thinker->data = data;
	thinker->total_meal = 0;
	thinker->is_eating = 0;
	thinker->timeout = data->die;
	thinker->rfork = i;
	thinker->lfork = ((i + 1) == data->nb) ? 0 : (i + 1);
	return (0);
}
