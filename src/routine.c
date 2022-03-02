/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsiguenz <tsiguenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 16:50:14 by tsiguenz          #+#    #+#             */
/*   Updated: 2022/03/02 16:12:02 by tsiguenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	p_action(t_philo *philo, char *message)
{
	if (pthread_mutex_lock(&philo->data->mutex) != 0)
		return (1);
	if (philo->data->stop == 0)
		printf("%ld %d %s\n", get_time(philo->data->start_time), philo->index, message);
	if (pthread_mutex_unlock(&philo->data->mutex) != 0)
		return (1);
	return (0);
}

static int	take_fork(t_philo *philo)
{
	if (philo->index != philo->data->nb_philo)
	{
		if (pthread_mutex_lock(&philo->fork[philo->index - 1]) != 0)
			return (1);
		if (p_action(philo, M_TAKE_FORK) != 0)
			return (1);
		if (pthread_mutex_lock(&philo->fork[philo->index]) != 0)
			return (1);
		if (p_action(philo, M_TAKE_FORK) != 0)
			return (1);
	}
	else
	{
		if (pthread_mutex_lock(&philo->fork[0]) != 0)
			return (1);
		if (p_action(philo, M_TAKE_FORK) != 0)
			return (1);
		if (pthread_mutex_lock(&philo->fork[philo->index - 1]) != 0)
			return (1);
		if (p_action(philo, M_TAKE_FORK) != 0)
			return (1);
	}
	return (0);
}

static int	left_fork(t_philo *philo)
{
	if (philo->index != philo->data->nb_philo)
	{
		if (pthread_mutex_unlock(&philo->fork[philo->index - 1]) != 0)
			return (1);
		if (pthread_mutex_unlock(&philo->fork[philo->index]) != 0)
			return (1);
	}
	else
	{
		if (pthread_mutex_unlock(&philo->fork[0]) != 0)
			return (1);
		if (pthread_mutex_unlock(&philo->fork[philo->index - 1]) != 0)
			return (1);
	}
	return (0);
}

static int	eat(t_philo *philo)
{
	if (take_fork(philo) == 1)
		return (1);
	if (p_action(philo, M_EAT) == 1)
		return (1);
	if (pthread_mutex_lock(&philo->data->mutex) != 0)
		return (1);
	philo->last_eat = get_time(philo->data->start_time);
	usleep(philo->data->time_to_eat * 1000);
	if (pthread_mutex_unlock(&philo->data->mutex) != 0)
		return (1);
	if (left_fork(philo) == 1)
		return (1);
	return (0);
}

static int	action(int action, t_philo *philo)
{
	if (action == EAT)
		if (eat(philo) != 0)
			return (1);
	if (action == SLEEP)
	{
		if (p_action(philo, M_SLEEP) == 1)
			return (1);
		usleep(philo->data->time_to_sleep * 1000);
	}
	if (action == THINK)
		if (p_action(philo, M_THINK) == 1)
			return (1);
	return (0);
}

void	*routine(void *arg)
{
	t_philo			*philo;

	philo = (t_philo *) arg;
	if (philo->index % 2 == 0)
		usleep(100);
	else
		usleep(50);
	while (42 && philo->data->stop == 0)
	{
		if (philo->data->nb_philo == 1)
		{
			p_action(philo, M_TAKE_FORK);
			p_action(philo, M_DEAD);
			return (NULL);
		}
		else
		{
			if (action(EAT, philo) != 0)
				return (NULL);
			if (action(SLEEP, philo) != 0)
				return (NULL);
			if (action(THINK, philo) != 0)
				return (NULL);
		}
	}
	return (NULL);
}
