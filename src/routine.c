/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsiguenz <tsiguenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 16:50:14 by tsiguenz          #+#    #+#             */
/*   Updated: 2022/02/28 01:30:25 by tsiguenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#define EAT "is eating"
#define THINK "is thinking"
#define SLEEP "is sleeping"

void	print_action(long time, int philo_nb, char *message)
{
	printf("%ld %d %s\n", time, philo_nb, message);
}

static void	eat(t_philo *philo)
{
	print_action(get_time(philo->data->start_time), philo->index, EAT);
	philo->last_eat = get_time(philo->data->start_time);
	usleep(philo->data->time_to_eat * 1000);
}

static void	think(t_philo *philo)
{
	print_action(get_time(philo->data->start_time), philo->index, THINK);
}

static void	sleeep(t_philo *philo)
{
	print_action(get_time(philo->data->start_time), philo->index, SLEEP);
	usleep(philo->data->time_to_sleep * 1000);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	eat(philo);
	think(philo);
	sleeep(philo);
	return (NULL);
}
