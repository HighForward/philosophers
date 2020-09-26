#include "../includes/philo_three.h"

int		check_input(char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int		init_struct(char **argv, t_data *data)
{
	if (check_input(argv) == 0)
		return (0);
	data->nb = ft_atoi(argv[0]);
	data->die = ft_atoi(argv[1]);
	data->eat = ft_atoi(argv[2]);
	data->sleep = ft_atoi(argv[3]);
	data->must_eat = (argv[4] != NULL ? ft_atoi(argv[4]) : 2147483647);
	data->state = 0;
	if (data->nb < 2 || data->nb > 200)
		return (return_str("must be > 2 && < 200\n", 0));
	return (1);
}