/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsiguenz <tsiguenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 16:50:14 by tsiguenz          #+#    #+#             */
/*   Updated: 2022/03/01 11:47:49 by tsiguenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	p_action(long time, int philo_nb, char *message)
{
	printf("%ld %d %s\n", time, philo_nb, message);
}

static void	eat(t_philo *philo)
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
	pthread_mutex_lock(&philo->fork[i]);
	p_action(get_time(philo->data->start_time), philo->index, M_TAKE_FORK);
	pthread_mutex_lock(&philo->fork[j]);
	p_action(get_time(philo->data->start_time), philo->index, M_TAKE_FORK);
	p_action(get_time(philo->data->start_time), philo->index, M_EAT);
	philo->last_eat = get_time(philo->data->start_time);
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->fork[j]);
	pthread_mutex_unlock(&philo->fork[i]);
}

static void	action(int action, t_philo *philo)
{
	if (action == EAT && philo->data->stop != 1)
		eat(philo);
	if (action == SLEEP && philo->data->stop != 1)
	{
		p_action(get_time(philo->data->start_time), philo->index, M_SLEEP);
		usleep(philo->data->time_to_sleep * 1000);
	}
	if (action == THINK && philo->data->stop != 1)
		p_action(get_time(philo->data->start_time), philo->index, M_THINK);
}

void	*routine(void *arg)
{
	t_philo			*philo;

	usleep(20);
	philo = (t_philo *) arg;
	while (42 && philo->data->stop == 0)
	{
		if (philo->data->nb_philo == 1)
		{
			p_action(get_time(philo->data->start_time), philo->index, \
				M_TAKE_FORK);
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
