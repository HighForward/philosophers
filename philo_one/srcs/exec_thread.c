#include "../includes/philo_one.h"

void *thread_1(void *arg)
{
    while (1)
    {
        t_time *temp;
        temp = arg;
        ft_putnbr(current_time((*temp)));
        ft_putstr(" 1 is eating\n");
        usleep(temp->eat * 1000);

        ft_putnbr(current_time((*temp)));
        ft_putstr(" 1 is sleeping\n");
        usleep(temp->sleep * 1000);
        gettimeofday(&temp->end, NULL);

        ft_putnbr(current_time((*temp)));
        ft_putstr(" 1 is thinking\n");
        usleep((temp->die - temp->sleep - temp->eat) * 1000);

    }
    pthread_exit(EXIT_SUCCESS);
}
