#include "../includes/philo_one.h"

int	init_struct(char **argv, t_data *data)
{
    data->nb = ft_atoi(argv[0]);
    data->die = ft_atoi(argv[1]);
    data->eat = ft_atoi(argv[2]);
    data->sleep = ft_atoi(argv[3]);
    if (argv[4] != NULL)
        data->must_eat = ft_atoi(argv[4]);
    else
        data->must_eat = 2147483647;
    pthread_mutex_init(&data->mutex_msg, NULL);
    return (1);
}