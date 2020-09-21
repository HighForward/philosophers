/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrignol <mbrignol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 18:31:13 by mbrignol          #+#    #+#             */
/*   Updated: 2020/09/19 16:55:39 by mbrignol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_two.h"

int		check_input(char **argv)
{
	int i;
	int j;

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
	data->nb_rest = data->nb;
	data->is_died = 0;
	if (argv[4] != NULL)
		data->must_eat = ft_atoi(argv[4]);
	else
		data->must_eat = 2147483647;
	return (1);
}

int		init_semaphore(t_data *data)
{
	sem_unlink("/sem_msg");
	sem_unlink("/take_fork");
	sem_unlink("/sem_fork");
	data->sem_msg = sem_open("/sem_msg", O_CREAT, 0664, 1);
	data->take_fork = sem_open("/take_fork", O_CREAT, 0664, 1);
	data->sem_fork = sem_open("/sem_fork", O_CREAT, 0664, data->nb);
	return (1);
}

int		init_thinker(t_philo *thinker, t_data *data, int i)
{
	sem_init(&thinker->sem_eat, 0, 1);
	thinker->index = i + 1;
	thinker->data = data;
	thinker->total_meal = 0;
	thinker->is_eating = 0;
	thinker->timeout = data->die;
	return (1);
}
