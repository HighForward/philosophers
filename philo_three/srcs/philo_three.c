#include "../includes/philo_three.h"

int create_thinkers(t_data *data, t_philo **thinker)
{
    int i;
    pid_t process;
    int end;
    int status;

    end = 0;
    i = 0;
    (*thinker) = malloc(sizeof(t_philo) * data->nb);

    gettimeofday(&data->start, NULL);
    while (i < data->nb)
    {
        init_thinker(&(*thinker)[i], data, i);
        create_process(data, &(*thinker)[i]);
        usleep(100);
        i++;
    }
    return (0);
}

int main(int argc, char **args)
{
    t_data data;
    t_philo *thinker;
    int status;

    if (argc < 5 || argc > 6)
        return (return_str("wrong arguments\n", 0));

    init_struct(args + 1, &data);
    init_semaphore(&data);
    if (create_thinkers(&data, &thinker) != 0)
        return (0);

    waitpid(-1, &status, 0);
//    while (alive_check(thinker, &data) == 1);

    return (0);
}