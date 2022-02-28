/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsiguenz <tsiguenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 15:09:47 by tsiguenz          #+#    #+#             */
/*   Updated: 2022/02/27 23:06:42 by tsiguenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_philo(t_philo *philo, pthread_mutex_t *fork, t_data *data)
{
	int	i;

	i = 0;
	gettimeofday(&data->start_time, NULL);
	while (i < data->nb_philo)
	{
		philo[i].is_dead = 0;
		philo[i].index = i + 1;
		philo[i].fork = fork;
		philo[i].data = data;
		pthread_mutex_init(&fork[i], NULL);
		pthread_create(&philo[i].thread, NULL, routine, &philo[i]);
		i++;
	}
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_join(philo[i].thread, NULL);
		pthread_mutex_destroy(&fork[i]);
		i++;
	}
	return (0);
}
