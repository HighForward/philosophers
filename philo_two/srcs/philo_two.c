/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrignol <mbrignol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 18:39:39 by mbrignol          #+#    #+#             */
/*   Updated: 2020/09/23 18:55:11 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_two.h"

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
			usleep(200);
		}
		i++;
	}
}

int		create_thinkers(t_data *data, t_philo **thinker)
{
	(*thinker) = malloc(sizeof(t_philo) * data->nb);
	gettimeofday(&data->start, NULL);
	init_semaphore(data);
	launch_thinker(thinker, data, 0);
	usleep(5000);
	launch_thinker(thinker, data, 1);
	return (0);
}

int		main(int argc, char **args)
{
	t_data	data;
	t_philo	*thinker;
	int i;

	i = 0;
	if (argc < 5 || argc > 6)
		return (return_str("wrong arguments\n", 0));
	if (init_struct(args + 1, &data) == 0)
		return (return_str("arguments wrong type\n", 0));
	if (create_thinkers(&data, &thinker) != 0)
		return (0);
	while (alive_check(thinker, &data) == 1)
		;
	while (data.nb_rest != 0)
	{
		sem_post(data.sem_msg);
		sem_post(data.sem_fork);
		sem_post(data.take_fork);
		ft_usleep(50);
	}
	while (i < data.nb)
	{
		sem_unlink(thinker[i].sem_eat_name);
		free(thinker[i].sem_eat_name);
		i++;
	}
	sem_post(data.sem_fork);
	sem_post(data.sem_msg);
	sem_post(data.take_fork);
	sem_unlink("/sem_fork");
	sem_unlink("/take_fork");
	sem_unlink("/sem_msg");
	free(thinker);
	return (0);
}
