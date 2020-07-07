#include "../includes/philo_one.h"

int create_thinkers(t_data *data)
{
    int i;
    t_philo *thinker;

    thinker = malloc(sizeof(t_philo) * data->nb);
    gettimeofday(&data->start, NULL);
    i = 0;
    while (i < data->nb)
    {
        thinker[i].index = i;
        thinker[i].data = data;
        thinker[i].ate = 0;
        pthread_mutex_init(&thinker[i].mutex, NULL);
        pthread_mutex_unlock(&thinker[i].mutex);
        pthread_create(&thinker[i].thread, NULL, client_thread, (void*)&thinker[i]);
        i++;
    }

    i = 0;
    while (i < data->nb)
    {
        pthread_detach(thinker[i].thread);
        i++;
    }

    while (alive_check(thinker) == 1);

    return (0);
}

int main(int argc, char **args)
{
    t_data data;

    if (argc < 5 || argc > 6)
        return (return_str("wrong arguments\n", 0));
    data = init_struct(args + 1);

    if (create_thinkers(&data) != 0)
        return (0);


    return (0);
}

//forks and speak = mutex pour pas que ça soit mélanger