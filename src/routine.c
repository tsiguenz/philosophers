/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsiguenz <tsiguenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 16:50:14 by tsiguenz          #+#    #+#             */
/*   Updated: 2022/02/23 20:10:30 by tsiguenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.c"

void	print_action(int time, int philo_nb, char *message)
{
	printf("%d %d %s\n", time, philo_nb, message);
}

static void	eat(t_philo *philo)
{
	timeval	time;

	time = NULL;
	print_action(0, phili->index, "is eating");
	gettimeofday(time, NULL);
	philo->last_eat = time.tv_usec;
	usleep(philo->time_eat * 1000);
}

static void	think(t_philo *philo)
{
	print_action(0, phili->index, "is thinking");
}

static void	sleeep(t_philo *philo)
{
	print_action(0, phili->index, "is sleeping");
	usleep(philo->time_to_sleep * 1000);
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
