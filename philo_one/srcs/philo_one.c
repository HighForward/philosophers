#include "../includes/philo_one.h"

void	print_struct(t_time time)
{
	printf("%d\n", time.nb);
	printf("%d\n", time.die);
	printf("%d\n", time.eat);
	printf("%d\n", time.sleep);
}

t_time	init_struct(char **argv)
{
	t_time init;

	init.nb = ft_atoi(argv[0]);
	init.die = ft_atoi(argv[1]);
	init.eat = ft_atoi(argv[2]);
	init.sleep = ft_atoi(argv[3]);
	init.life = 1;
	return (init);
}

int		philo_start(t_time time)
{
    gettimeofday(&time.start, NULL);
    pthread_t thread;

    pthread_create(&thread, NULL, thread_1, &time);
    pthread_join(thread, NULL);
	return (1);
}

int main(int argc, char **args)
{
    t_time thinker;

    if (argc <= 4 || argc > 6)
        return (return_str("Wrong arguments\n", 0));
    thinker = init_struct(args + 1);

    philo_start(thinker);
    return (0);
}

//forks and speak = mutex pour pas que ça soit mélanger