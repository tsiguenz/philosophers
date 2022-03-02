/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsiguenz <tsiguenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 18:30:15 by tsiguenz          #+#    #+#             */
/*   Updated: 2022/03/02 16:14:53 by tsiguenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <limits.h>
# include <sys/time.h>

# define EAT 0
# define THINK 1
# define SLEEP 2
# define TAKE_FORK 3
# define M_EAT "is eating"
# define M_THINK "is thinking"
# define M_SLEEP "is sleeping"
# define M_TAKE_FORK "has taken a fork"
# define M_DEAD "died"

typedef struct timeval	t_timeval;

typedef struct s_data
{
	t_timeval		start_time;
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				iteration;
	int				stop;
	pthread_mutex_t	mutex;
}				t_data;

typedef struct s_philo
{
	int				index;
	long			last_eat;
	long			last_sleep;
	int				is_dead;
	pthread_t		thread;
	t_data			*data;
	pthread_mutex_t	*fork;
}				t_philo;

int		parsing(int argc, char **argv, t_data *data);
int		init_philo(t_philo *philo, pthread_mutex_t *fork, t_data *data);
void	*routine(void *arg);
int		p_action(t_philo *philo, char *message);
long	get_time(t_timeval start);
int		check_death(t_philo *philo, t_data *data);
int		ft_free(t_philo *philo, pthread_mutex_t *fork);
int		ft_exit(t_data *data, t_philo *philo, pthread_mutex_t *fork);
#endif
