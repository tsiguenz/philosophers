/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsiguenz <tsiguenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 15:09:47 by tsiguenz          #+#    #+#             */
/*   Updated: 2022/03/01 17:25:27 by tsiguenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_philo(t_philo *philo, pthread_mutex_t *fork, t_data *data)
{
	int	i;

	i = 0;
	if (gettimeofday(&data->start_time, NULL) == -1)
		return (1);
	while (i < data->nb_philo)
	{
		philo[i].is_dead = 0;
		philo[i].index = i + 1;
		philo[i].fork = fork;
		philo[i].data = data;
		philo[i].last_eat = 0;
		if (pthread_mutex_init(&fork[i], NULL) != 0)
			return (1);
		if (pthread_create(&philo[i].thread, NULL, routine, &philo[i]) != 0)
			return (1);
		usleep(50);
		i++;
	}
	if (check_death(philo, data) != 0)
		return (1);
	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_join(philo[i].thread, NULL) != 0)
			return (1);
		if (pthread_mutex_destroy(&fork[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}
