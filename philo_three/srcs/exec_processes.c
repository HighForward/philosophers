#include "../includes/philo_three.h"

int is_eating(t_philo thinker)
{
    sem_wait(&thinker.sem_eat);
    if (thinker.is_eating == 0)
    {
        sem_post(&thinker.sem_eat);
        return (0);
    }
    sem_post(&thinker.sem_eat);
    return (1);
}

void *alive_check(void *arg)
{
    t_philo *thinker;

    thinker = (t_philo*)arg;
    while (1)
    {
        if (thinker->total_meal >= thinker->data->must_eat)
        {
            message_alert(current_time((*thinker->data)), thinker->index, thinker, FED);
            exit(EXIT_SUCCESS);
        }
        if (thinker->timeout < current_time((*thinker->data)))
        {
            message_alert(current_time((*thinker->data)), thinker->index, thinker, DIED);
            exit(EXIT_SUCCESS);
        }
        usleep(30);
    }
    exit(EXIT_SUCCESS);
}

int create_process(t_data *data, t_philo *thinker)
{
    thinker->pid = fork();
    if (thinker->pid == 0)
    {
        data->sem_msg = sem_open("/sem_msg", O_RDWR);
        data->sem_fork = sem_open("/sem_fork", O_RDWR);
        pthread_create(&thinker->thread, NULL, alive_check, (void*)thinker);
        pthread_detach(thinker->thread);
        while (1)
        {
            sem_wait(data->sem_fork);
            message_alert(current_time((*thinker->data)), thinker->index, thinker, FORK);
            sem_wait(data->sem_fork);
            message_alert(current_time((*thinker->data)), thinker->index, thinker, FORK);


            message_alert(current_time((*thinker->data)), thinker->index, thinker, EAT);
            thinker->timeout = current_time((*thinker->data)) + (thinker->data->die);
            thinker->is_eating = 1;
            usleep(thinker->data->eat * 1000);
            thinker->is_eating = 0;
            thinker->total_meal++;

            sem_post(data->sem_fork);
            sem_post(data->sem_fork);


            message_alert(current_time((*thinker->data)), thinker->index, thinker, SLEEP);
            usleep(thinker->data->sleep * 1000);



            message_alert(current_time((*thinker->data)), thinker->index, thinker, THINK);
        }
    }
    return (0);
}
