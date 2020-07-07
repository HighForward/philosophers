#include "../includes/philo_one.h"

t_data	init_struct(char **argv)
{
    t_data init;

    init.nb = ft_atoi(argv[0]);
    init.die = ft_atoi(argv[1]);
    init.eat = ft_atoi(argv[2]);
    init.sleep = ft_atoi(argv[3]);
    if (argv[4] != NULL)
        init.must_eat = ft_atoi(argv[4]);
    else
        init.must_eat = 2147483647;
    return (init);
}