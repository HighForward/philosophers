/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrignol <mbrignol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 20:18:27 by mbrignol          #+#    #+#             */
/*   Updated: 2020/09/23 23:36:58 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_three.h"

int 	wait_and_kill(t_data *data)
{
	pthread_t death_check;
	int		status;
	int i = 0;

	pthread_create(&death_check, NULL, death, (void*)data);
	pthread_detach(death_check);
	sem_wait(data->stop);
	if (data->state == 0)
	{
		while (waitpid(-1, &status, 0) > 0)
			;
		if (WIFEXITED(status))
		{
			if (WEXITSTATUS(status) == FED)
				write(1, "everyone is fed\n", 16);
		}
	}
	else
	{
		while (i < data->nb)
		{
			kill(data->pid[i], SIGKILL);
			i++;
		}
	}
	while (waitpid(-1, &status, 0) > 0)
		;
	return (1);
}

void	launch_thinker(t_philo **thinker, t_data *data, int mid)
{
	int i;

	i = 0;
	while (i < data->nb)
	{
		if (i % 2 == mid)
		{
			init_thinker(&(*thinker)[i], data, i);
			create_process(data, &(*thinker)[i], i);
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
	if (init_struct(args + 1, &data) == 0)
		return (return_str("arguments wrong type\n", 0));
	if (create_thinkers(&data, &thinker) != 0)
		return (0);
	wait_and_kill(&data);
	i = 0;
	while (i < data.nb)
	{
 		sem_unlink(thinker[i].sem_eat_name);
		free(thinker[i].sem_eat_name);
		i++;
	}
	sem_unlink("/sem_fork");
	sem_unlink("/sem_msg");
	sem_unlink("/take_fork");
	sem_unlink("/stop");
	sem_unlink("/death");
	free(data.pid);
	free(thinker);
	return (0);
}
