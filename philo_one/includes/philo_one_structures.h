#ifndef PHILO_ONE_STRUCTURES_H
#define PHILO_ONE_STRUCTURES_H

typedef struct	s_time
{
    int life;
	int nb;
	int die;
	int eat;
	int sleep;
    struct timeval start;
    struct timeval end;
}				t_time;

#endif
