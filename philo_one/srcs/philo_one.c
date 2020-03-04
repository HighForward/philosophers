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
	return (init);
}

int		get_exec_time()
{
	struct timeval start;
	struct timeval end;
	int i;

	i = 45645;
	gettimeofday (&start, NULL);

	/* tes instructions */
	while (i > 0)
		i--;
	gettimeofday (&end, NULL);
	printf("millisecondes: %ld\n", ((end.tv_sec - start.tv_sec) * 1000000 + end.tv_usec) - start.tv_usec);
	return (0);
}

int		rekt_dat_shit(t_time time)
{
	get_exec_time();
	get_thread(time);
	return (1);
}

int main(int argc, char **args)
{
	t_time thinker;
	if (argc <= 4 || argc > 6)
	{
		ft_putstr("Wrong number of arguments");
		return (1);
	}
	thinker = init_struct(args + 1);
//	print_struct(thinker);
	rekt_dat_shit(thinker);
	return (0);
}