#include "../includes/philo_two.h"

int create_thinkers(t_data *data, t_philo **thinker)
{
    int i;

    i = 0;
    (*thinker) = malloc(sizeof(t_philo) * data->nb);

    gettimeofday(&data->start, NULL);
    while (i < data->nb)
    {
        init_thinker(&(*thinker)[i], data, i);
        pthread_create(&(*thinker)[i].thread, NULL, client_thread, (void*)&(*thinker)[i]);
        pthread_detach((*thinker)[i].thread);
        usleep(300);
        i++;
    }
    return (0);
}

int main(int argc, char **args)
{
    t_data data;
    t_philo *thinker;
    int i;

    sem_unlink("/sem_msg");
    sem_unlink("/sem_fork");

    if (argc < 5 || argc > 6)
        return (return_str("wrong arguments\n", 0));

    init_struct(args + 1, &data);
    init_semaphore(&data);
    if (create_thinkers(&data, &thinker) != 0)
        return (0);

    while (alive_check(thinker, &data) == 1);

    sem_close(data.sem_msg);
    sem_close(data.sem_fork);
    sem_unlink("/sem_msg");
    sem_unlink("/sem_fork");
    i = 0;
    while (i < data.nb)
    {
        sem_close(&thinker[i].sem_eat);
        i++;
    }
    return (0);
}