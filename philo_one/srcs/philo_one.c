#include "../includes/philo_one.h"

//pthread_mutex_t mutex = PTHREAD_ERRORCHECK_MUTEX_INITIALIZER_NP;

int create_thinkers(t_data *data, t_philo **thinker)
{
    int i;

    i = 0;
    (*thinker) = malloc(sizeof(t_philo) * data->nb);
    data->forks = malloc(sizeof(pthread_mutex_t) * data->nb);

    init_mutex(data);
    gettimeofday(&data->start, NULL);
    while (i < data->nb)
    {
        init_thinker(&(*thinker)[i], data, i);
        pthread_create(&(*thinker)[i].thread, NULL, client_thread, (void*)&(*thinker)[i]);
        pthread_detach((*thinker)[i].thread);
//        usleep(100);
        i++;
    }
    return (0);
}

int main(int argc, char **args)
{
    t_data data;
    t_philo *thinker;

    if (argc < 5 || argc > 6)
        return (return_str("wrong arguments\n", 0));

    init_struct(args + 1, &data);

    if (create_thinkers(&data, &thinker) != 0)
        return (0);

    while (alive_check(thinker, &data) == 1);
//    pthread_mutex_destroy(&data.mutex_msg);

    return (0);
}