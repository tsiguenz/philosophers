/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsiguenz <tsiguenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 16:50:14 by tsiguenz          #+#    #+#             */
/*   Updated: 2022/03/01 18:25:22 by tsiguenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	p_action(long time, t_philo *philo, char *message)
{
	if (pthread_mutex_lock(&philo->data->mutex) != 0)
		return (1);
	if (philo->data->stop == 0)
		printf("%ld %d %s\n", time, philo->index, message);
	if (pthread_mutex_unlock(&philo->data->mutex) != 0)
		return (1);
	return (0);
}

static int	eat(t_philo *philo)
{
	int	i;
	int	j;

	if (philo->index == philo->data->nb_philo)
	{
		i = 0;
		j = philo->index - 1;
	}
	else
	{
		i = philo->index - 1;
		j = philo->index;
	}
	if (pthread_mutex_lock(&philo->fork[i]) != 0)
		return (1);
	if (p_action(get_time(philo->data->start_time), philo, M_TAKE_FORK) != 0)
		return (1);
	if (pthread_mutex_lock(&philo->fork[j]) != 0)
		return (1);
	if (p_action(get_time(philo->data->start_time), philo, M_TAKE_FORK) != 0)
		return (1);
	if (p_action(get_time(philo->data->start_time), philo, M_EAT) != 0)
		return (1);
	if (pthread_mutex_lock(&philo->data->mutex) != 0)
		return (1);
	philo->last_eat = get_time(philo->data->start_time);
	if (philo->last_eat == -1)
		return (1);
	usleep(philo->data->time_to_eat * 1000);
	if (pthread_mutex_unlock(&philo->data->mutex) != 0)
		return (1);
	if (pthread_mutex_unlock(&philo->fork[j]) != 0)
		return (1);
	if (pthread_mutex_unlock(&philo->fork[i]) != 0)
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
		p_action(get_time(philo->data->start_time), philo, M_SLEEP);
		usleep(philo->data->time_to_sleep * 1000);
	}
	if (action == THINK)
		p_action(get_time(philo->data->start_time), philo, M_THINK);
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
			p_action(get_time(philo->data->start_time), philo, M_TAKE_FORK);
			return (NULL);
		}
		else
		{
			if (action(EAT, philo) != 0)
				return (NULL);
			action(SLEEP, philo);
			action(THINK, philo);
		}
	}
	return (NULL);
}
