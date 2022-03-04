/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsiguenz <tsiguenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 16:50:14 by tsiguenz          #+#    #+#             */
/*   Updated: 2022/03/04 17:25:17 by tsiguenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
	int	time_to_eat;

	if (action == EAT && is_dead(philo) == 0)
	{
		take_fork(philo);
		p_action(philo, M_EAT);
		pthread_mutex_lock(&philo->data->mutex);
		philo->last_eat = get_time(philo->data->start_time);
		time_to_eat = philo->data->time_to_eat;
		pthread_mutex_unlock(&philo->data->mutex);
		usleep(time_to_eat * 1000);
		left_fork(philo);
		usleep(100);
	}
	if (action == SLEEP && is_dead(philo) == 0)
	{
		p_action(philo, M_SLEEP);
		usleep(philo->data->time_to_sleep * 1000);
	}
	if (action == THINK && is_dead(philo) == 0)
	{
		p_action(philo, M_THINK);
		usleep(100);
	}
}

static int	loop_routine(t_philo *philo, int nb, int *iteration)
{
	while (42 && *iteration != 0 && is_dead(philo) == 0)
	{
		if (nb == 1)
		{
			p_action(philo, M_TAKE_FORK);
			return (1);
		}
		else
		{
			action(EAT, philo);
			action(SLEEP, philo);
			action(THINK, philo);
		}
		if (*iteration != -2)
			(*iteration)--;
	}
	return (0);
}

void	*routine(void *arg)
{
	t_philo			*philo;
	int				nb;
	int				iteration;

	philo = (t_philo *) arg;
	pthread_mutex_lock(&philo->data->mutex);
	nb = philo->data->nb_philo;
	iteration = philo->data->iteration;
	pthread_mutex_unlock(&philo->data->mutex);
	if (philo->index % 2 == 1)
		usleep(40000);
	if (loop_routine(philo, nb, &iteration) == 1)
		return (NULL);
	if (iteration == 0)
	{
		pthread_mutex_lock(&philo->data->mutex);
		philo->data->iteration = 0;
		pthread_mutex_unlock(&philo->data->mutex);
	}
	return (NULL);
}
