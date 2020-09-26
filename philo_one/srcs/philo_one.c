/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 04:34:50 by user42            #+#    #+#             */
/*   Updated: 2020/09/26 03:32:02 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

void	launch_thinker(t_philo **thinker, t_data *data, int mid)
{
	int i;

	i = 0;
	while (i < data->nb)
	{
		if (i % 2 == mid)
		{
			init_thinker(&(*thinker)[i], data, i);
			pthread_create(&(*thinker)[i].thread, NULL,
			client_thread, (void*)&(*thinker)[i]);
			pthread_detach((*thinker)[i].thread);
		}
		i++;
	}
}

int		create_thinkers(t_data *data, t_philo **thinker)
{
	(*thinker) = malloc(sizeof(t_philo) * data->nb);
	data->forks = malloc(sizeof(t_fork) * data->nb);
	gettimeofday(&data->start, NULL);
	init_mutex(data);
	launch_thinker(thinker, data, 0);
	ft_usleep(5000);
	launch_thinker(thinker, data, 1);
	return (0);
}

void	wait_clear_exit(t_data *data, t_philo *thinker)
{
	int i;

	i = 0;
	while (data->nb_rest != 0)
	{
		i = 0;
		pthread_mutex_unlock(&data->mutex_msg);
		while (i < data->nb)
		{
			pthread_mutex_unlock(&thinker[i].mutex_eat);
			pthread_mutex_unlock(&data->forks[i].mutex);
			i++;
		}
		ft_usleep(50);
	}
}

int		main(int argc, char **args)
{
	t_data	data;
	t_philo	*thinker;
	int		i;

	i = 0;
	if (argc < 5 || argc > 6)
		return (return_str("wrong arguments\n", 0));
	if (init_struct(args + 1, &data) == 0)
		return (return_str("arguments wrong type\n", 0));
	if (create_thinkers(&data, &thinker) != 0)
		return (0);
	while (alive_check(thinker, &data) == 1)
		;
	wait_clear_exit(&data, thinker);
	i = 0;
	while (i < data.nb)
	{
		pthread_mutex_destroy(&thinker[i].mutex_eat);
		pthread_mutex_destroy(&data.forks[i].mutex);
		i++;
	}
	pthread_mutex_destroy(&data.mutex_msg);
	free(data.forks);
	free(thinker);
	return (0);
}
