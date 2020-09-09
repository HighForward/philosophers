/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrignol <mbrignol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 18:39:39 by mbrignol          #+#    #+#             */
/*   Updated: 2020/09/09 18:39:40 by mbrignol         ###   ########.fr       */
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
	int		i;

	if (argc < 5 || argc > 6)
		return (return_str("wrong arguments\n", 0));
	init_struct(args + 1, &data);
	if (create_thinkers(&data, &thinker) != 0)
		return (0);
	while (alive_check(thinker, &data) == 1)
		;
	sem_close(data.sem_msg);
	sem_close(data.sem_fork);
	sem_close(data.take_fork);
	sem_unlink("/sem_msg");
	sem_unlink("/sem_fork");
	sem_unlink("/take_fork");
	i = 0;
	while (i < data.nb)
	{
		sem_close(&thinker[i].sem_eat);
		i++;
	}
	free(thinker);
	return (0);
}
