/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsiguenz <tsiguenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 16:50:14 by tsiguenz          #+#    #+#             */
/*   Updated: 2022/03/01 00:28:06 by tsiguenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#define EAT 0
#define THINK 1
#define SLEEP 2
#define TAKE_FORK 3
#define M_EAT "is eating"
#define M_THINK "is thinking"
#define M_SLEEP "is sleeping"
#define M_TAKE_FORK "has taken a fork"

void	p_action(long time, int philo_nb, char *message, pthread_mutex_t m)
{
	pthread_mutex_lock(&m);
	printf("%ld %d %s\n", time, philo_nb, message);
	pthread_mutex_unlock(&m);
}

static void	action(int	action, t_philo *philo, pthread_mutex_t m)
{
	if (action == EAT)
	{
		if (philo->index == philo->data->nb_philo)
		{
			pthread_mutex_lock(&philo->fork[0]);
			p_action(get_time(philo->data->start_time), philo->index, M_TAKE_FORK, m);
			pthread_mutex_lock(&philo->fork[philo->index - 1]);
			p_action(get_time(philo->data->start_time), philo->index, M_TAKE_FORK, m);
			p_action(get_time(philo->data->start_time), philo->index, M_EAT, m);
			philo->last_eat = get_time(philo->data->start_time);
			usleep(philo->data->time_to_eat * 1000);
			pthread_mutex_unlock(&philo->fork[philo->index - 1]);
			pthread_mutex_unlock(&philo->fork[0]);
		}
		else
		{
			pthread_mutex_lock(&philo->fork[philo->index - 1]);
			p_action(get_time(philo->data->start_time), philo->index, M_TAKE_FORK, m);
			pthread_mutex_lock(&philo->fork[philo->index]);
			p_action(get_time(philo->data->start_time), philo->index, M_TAKE_FORK, m);
			p_action(get_time(philo->data->start_time), philo->index, M_EAT, m);
			philo->last_eat = get_time(philo->data->start_time);
			usleep(philo->data->time_to_eat * 1000);
			pthread_mutex_unlock(&philo->fork[philo->index]);
			pthread_mutex_unlock(&philo->fork[philo->index - 1]);
		}
	}
	if (action == SLEEP)
	{
		p_action(get_time(philo->data->start_time), philo->index, M_SLEEP, m);
		usleep(philo->data->time_to_sleep * 1000);
	}
	if (action == THINK)
		p_action(get_time(philo->data->start_time), philo->index, M_THINK, m);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	pthread_mutex_t	mutex_print;

	usleep(20);
	pthread_mutex_init(&mutex_print, NULL);
	philo = (t_philo *) arg;
	action(EAT, philo, mutex_print);
	action(SLEEP, philo, mutex_print);
	action(THINK, philo, mutex_print);
	pthread_mutex_destroy(&mutex_print);
	return (NULL);
}
