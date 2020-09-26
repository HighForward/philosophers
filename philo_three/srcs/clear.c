#include "../includes/philo_three.h"

void 	clear_child_exit(t_philo *t, t_data *data)
{
	sem_close(data->sem_msg);
	sem_close(data->take_fork);
	sem_close(data->sem_fork);
	sem_close(data->stop);
	sem_close(data->death);
	free(t);
	free(data->pid);
	exit(0);
}

void	*death(void *arg)
{
	t_data *data;

	data = (t_data*)arg;
	sem_wait(data->death);
	data->state = 1;
	sem_post(data->stop);
	return (NULL);
}

int		wait_and_kill(t_data *data)
{
	pthread_t	death_check;
	int			status;
	int			i;

	i = 0;
	pthread_create(&death_check, NULL, death, (void*)data);
	pthread_detach(death_check);
	sem_wait(data->stop);
	if (data->state == 0)
	{
		sem_post(data->death);
		while (waitpid(-1, &status, 0) > 0)
			;
		write(1, "everyone is fed\n", 16);
	}
	else
	{
		while (i < data->nb)
			kill(data->pid[i++], SIGKILL);
	}
	while (waitpid(-1, &status, 0) > 0)
		;
	usleep(1000);
	return (1);
}

void	clear(t_data *data)
{
//	int i;
//
//	i = 0;
//	while (i < data->nb)
//	{
//		sem_close(t[i].sem_eat);
//		sem_unlink(t[i].sem_eat_name);
//		free(t[i].sem_eat_name);
//		i++;
//	}
	sem_close(data->sem_msg);
	sem_close(data->take_fork);
	sem_close(data->sem_fork);
	sem_close(data->stop);
	sem_close(data->death);
	sem_unlink("/sem_msg");
	sem_unlink("/take_fork");
	sem_unlink("/sem_fork");
	sem_unlink("/stop");
	sem_unlink("/death");
}