/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsiguenz <tsiguenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 16:50:14 by tsiguenz          #+#    #+#             */
/*   Updated: 2022/03/02 18:44:13 by tsiguenz         ###   ########.fr       */
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

static void	eat(t_philo *philo)
{
	take_fork(philo);
	p_action(philo, M_EAT);
	pthread_mutex_lock(philo->mutex);
	philo->last_eat = get_time(philo->data->start_time);
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(philo->mutex);
	left_fork(philo);
}

static void	action(int action, t_philo *philo)
{
	if (action == EAT)
		eat(philo);
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

	philo = (t_philo *) arg;
	while (42 && philo->data->stop == 0)
	{
		if (philo->data->nb_philo == 1)
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
	}
	return (NULL);
}
