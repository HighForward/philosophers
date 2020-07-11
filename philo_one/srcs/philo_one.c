#include "../includes/philo_one.h"

int create_thinkers(t_data *data, t_philo **thinker)
{
    int i;
    int odd;

    odd = (data->nb % 2 == 0 ? 1 : 0);
    i = 0;
    (*thinker) = malloc(sizeof(t_philo) * data->nb);
    data->forks = malloc(sizeof(pthread_mutex_t) * data->nb);
    data->forks_av = malloc(sizeof(int) * data->nb);
    int *tab;

    tab = malloc(sizeof(int) * data->nb);

    while (i < data->nb)
    {
        data->forks_av[i] = 0;
        i++;
    }
    i = 0;
    init_mutex(data);
    gettimeofday(&data->start, NULL);
    while (i < data->nb)
    {
        if (i % 2 == 0 && i < data->nb - odd)
        {
            tab[i] = 1;
            init_thinker(&(*thinker)[i], data, i);
            pthread_create(&(*thinker)[i].thread, NULL, client_thread, (void*)&(*thinker)[i]);
            pthread_detach((*thinker)[i].thread);
        }
        else
            tab[i] = 0;
        i++;
    }
    usleep(5000);
    i = 0;
    while (i < data->nb)
    {
        if (tab[i] == 0)
        {
            init_thinker(&(*thinker)[i], data, i);
            pthread_create(&(*thinker)[i].thread, NULL, client_thread, (void *) &(*thinker)[i]);
            pthread_detach((*thinker)[i].thread);
        }
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