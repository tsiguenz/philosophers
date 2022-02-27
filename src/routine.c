/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsiguenz <tsiguenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 16:50:14 by tsiguenz          #+#    #+#             */
/*   Updated: 2022/02/27 02:07:25 by tsiguenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_action(int time, int philo_nb, char *message)
{
	printf("%d %d %s\n", time, philo_nb, message);
}

static void	eat(t_philo *philo)
{
	struct timeval	time;

	print_action(philo->data->start_time, philo->index, "is eating");
	gettimeofday(&time, NULL);
	philo->last_eat = time.tv_usec;
	usleep(philo->data->time_to_eat * 1000);
	printf("%lu\n", time.tv_usec);
}

static void	think(t_philo *philo)
{
	print_action(philo->data->start_time, philo->index, "is thinking");
}

static void	sleeep(t_philo *philo)
{
	print_action(philo->data->start_time, philo->index, "is sleeping");
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
