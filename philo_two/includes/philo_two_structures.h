#ifndef PHILO_TWO_STRUCTURES_H
#define PHILO_TWO_STRUCTURES_H

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
    sem_t sem_msg;
    sem_t sem_fork;
}				t_data;

typedef struct  s_philo
{
    pthread_t thread;
    t_data *data;
    int index;
    int is_eating;
    sem_t sem_eat;
    int total_meal;
    int timeout;
    int lfork;
    int rfork;
}               t_philo;

#endif
