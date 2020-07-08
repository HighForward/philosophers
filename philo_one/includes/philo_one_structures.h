#ifndef PHILO_ONE_STRUCTURES_H
#define PHILO_ONE_STRUCTURES_H

#define EAT 1
#define SLEEP 2
#define THINK 3
#define FORK 4
#define DIED 5
#define FED 6


typedef struct	s_data
{
	int nb;
	int die;
	int eat;
	int sleep;
	int must_eat;
    struct timeval start;
    pthread_mutex_t mutex_msg;
}				t_data;

typedef struct  s_philo
{
    pthread_t thread;
    int index;
    int is_eating;
    int ate;
    int last_eat;
    int timeout;
    t_data *data;
}               t_philo;

#endif
