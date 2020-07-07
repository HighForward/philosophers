#ifndef PHILO_ONE_STRUCTURES_H
#define PHILO_ONE_STRUCTURES_H

typedef struct	s_data
{
	int nb;
	int die;
	int eat;
	int sleep;
	int must_eat;
    struct timeval start;
}				t_data;

typedef struct  s_philo
{
    pthread_t thread;
    pthread_mutex_t mutex;
    int index;
    int ate;
    int left;
    int right;
    t_data *data;
}               t_philo;

#endif
