/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsiguenz <tsiguenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 18:30:15 by tsiguenz          #+#    #+#             */
/*   Updated: 2022/02/27 21:41:13 by tsiguenz         ###   ########.fr       */
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

typedef struct s_data
{
	long		start_time;
	int			nb_philo;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			iteration;
}				t_data;

typedef struct s_philo
{
	int					index;
	suseconds_t			last_eat;
	suseconds_t			last_sleep;
	int					is_dead;
	pthread_t			thread;
	t_data				*data;
	pthread_mutex_t		*fork;
}				t_philo;

int		parsing(int argc, char **argv, t_data *data);
int		init_philo(t_philo *philo, pthread_mutex_t *fork, t_data *data);
void	*routine(void *arg);
void	print_action(int time, int philo_nb, char *message);
long	get_time(long start);
#endif
