/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrignol <mbrignol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 20:18:27 by mbrignol          #+#    #+#             */
/*   Updated: 2020/09/26 09:20:11 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_three.h"

int		create_process(t_philo *t, t_data *data, int i)
{
	if ((data->pid[i] = fork()) == 0)
	{
		pthread_create(&t->thread, NULL, alive_check, (void*)&t[i]);
		pthread_detach(t->thread);
		client_loop(data, &t[i]);
		clear_child_exit(t, data);
	}
}

void	launch_thinker(t_philo *t, t_data *data, int mid)
{
	int i;

	i = 0;
	while (i < data->nb)
	{
		if (i % 2 == mid)
		{
			init_thinker(&t[i], data, i);
			create_process(t, data, i);
			usleep(200);
		}
		i++;
	}
}

int		create_thinkers(t_data *data, t_philo *t)
{
	gettimeofday(&data->start, NULL);
	init_semaphore(data);

	launch_thinker(t, data, 0);
	usleep(5000);
	launch_thinker(t, data, 1);
	return (0);
}

int		main(int argc, char **args)
{
	t_data	data;
	t_philo	*t;

	if (argc < 5 || argc > 6)
		return (return_str("wrong arguments\n", 0));

	if (init_struct(args + 1, &data) == 0)
		return (return_str("arguments wrong type\n", 0));

	t = malloc(sizeof(t_philo) * data.nb);
	data.pid = malloc(sizeof(pid_t) * data.nb);

	if (create_thinkers(&data, t) != 0)
		return (0);

	wait_and_kill(&data);


	clear(&data);
	free(t);
	free(data.pid);
	return (0);
}
