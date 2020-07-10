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
    pthread_mutex_t *forks;
    pthread_mutex_t take_fork;
}				t_data;

typedef struct  s_philo
{
    pthread_t thread;
    t_data *data;
    int index;
    int is_eating;
    int total_meal;
    int timeout;
    int lfork;
    int rfork;
}               t_philo;

#endif
