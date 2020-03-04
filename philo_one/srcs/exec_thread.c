#include "../includes/philo_one.h"

void *thread_1(void *arg)
{
	int *temp;
	temp = (int *)arg;
	(*temp)++;
	ft_putstr("Nous sommes dans le thread.\n");
	pthread_exit(EXIT_SUCCESS);
}
int		get_thread(t_time time)
{
	int i;
	i = 0;
	pthread_t thread1;
	ft_putstr("Avant la création du thread.\n");
	pthread_create(&thread1, NULL, thread_1, &i);
	pthread_join(thread1, NULL);
	ft_putstr("Après la création du thread.\n");
	printf("%d\n", i);
	return (EXIT_SUCCESS);
}