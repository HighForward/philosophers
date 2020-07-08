#include "../includes/philo_one.h"

int create_thinkers(t_data *data, t_philo **thinker)
{
    int i;

    (*thinker) = malloc(sizeof(t_philo) * data->nb);
    gettimeofday(&data->start, NULL);
    i = 0;
    while (i < data->nb)
    {
        (*thinker)[i].index = i + 1;
        (*thinker)[i].data = data;
        (*thinker)[i].ate = 0;
        (*thinker)[i].last_eat = 0;
        (*thinker)[i].is_eating = 0;
        (*thinker)[i].timeout = data->die;
        pthread_create(&(*thinker)[i].thread, NULL, client_thread, (void*)&(*thinker)[i]);
        i++;
//        usleep(20);
    }
    i = 0;
    while (i < data->nb)
    {
        pthread_detach((*thinker)[i].thread);
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
    pthread_mutex_destroy(&data.mutex_msg);

    return (0);
}

//forks and speak = mutex pour pas que ça soit mélanger