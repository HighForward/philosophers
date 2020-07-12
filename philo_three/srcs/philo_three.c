#include "../includes/philo_three.h"

int create_thinkers(t_data *data, t_philo **thinker)
{
    int i;
    int odd;
    int *tab;

    i = 0;
    (*thinker) = malloc(sizeof(t_philo) * data->nb);
    tab = malloc(sizeof(int) * data->nb);
    odd = (data->nb % 2 == 0 ? 1 : 0);
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
    init_semaphore(&data);
    if (create_thinkers(&data, &thinker) != 0)
        return (0);

    while (alive_check(thinker, &data) == 1);

    return (0);
}