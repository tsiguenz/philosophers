/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsiguenz <tsiguenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 16:50:14 by tsiguenz          #+#    #+#             */
/*   Updated: 2022/03/03 19:11:58 by tsiguenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	p_action(t_philo *philo, char *message)
{
	pthread_mutex_lock(philo->mutex);
	if (philo->data->stop == 0)
		printf("%ld %d %s\n", get_time(philo->data->start_time), philo->index, message);
	pthread_mutex_unlock(philo->mutex);
}

static void	take_fork(t_philo *philo)
{
	if (philo->index != philo->data->nb_philo)
	{
		pthread_mutex_lock(&philo->fork[philo->index - 1]);
		p_action(philo, M_TAKE_FORK);
		pthread_mutex_lock(&philo->fork[philo->index]);
		p_action(philo, M_TAKE_FORK);
	}
	else
	{
		pthread_mutex_lock(&philo->fork[0]);
		p_action(philo, M_TAKE_FORK);
		pthread_mutex_lock(&philo->fork[philo->index - 1]);
		p_action(philo, M_TAKE_FORK);
	}
}

static void	left_fork(t_philo *philo)
{
	if (philo->index != philo->data->nb_philo)
	{
		pthread_mutex_unlock(&philo->fork[philo->index]);
		pthread_mutex_unlock(&philo->fork[philo->index - 1]);
	}
	else
	{
		pthread_mutex_unlock(&philo->fork[philo->index - 1]);
		pthread_mutex_unlock(&philo->fork[0]);
	}
}

static void	action(int action, t_philo *philo)
{
	if (action == EAT)
	{
		take_fork(philo);
		p_action(philo, M_EAT);
		philo->last_eat = get_time(philo->data->start_time);
		usleep(philo->data->time_to_eat * 1000);
		left_fork(philo);
	}
	if (action == SLEEP)
	{
		p_action(philo, M_SLEEP);
		usleep(philo->data->time_to_sleep * 1000);
	}
	if (action == THINK)
		p_action(philo, M_THINK);
}

void	*routine(void *arg)
{
	t_philo			*philo;
	int				nb;
	int				iteration;

	philo = (t_philo *) arg;
	pthread_mutex_lock(philo->mutex);
	nb = philo->data->nb_philo;
	iteration = philo->data->iteration;
	pthread_mutex_unlock(philo->mutex);
	if (philo->index % 2 == 1)
		usleep(40000);
	while (42 && iteration != 0)
	{
		if (nb == 1)
		{
			p_action(philo, M_TAKE_FORK);
			return (NULL);
		}
		else
		{
			action(EAT, philo);
			action(SLEEP, philo);
			action(THINK, philo);
		}
		if (iteration != -2)
			iteration--;
	}
	return (NULL);
}
