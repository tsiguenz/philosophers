/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsiguenz <tsiguenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 15:09:47 by tsiguenz          #+#    #+#             */
/*   Updated: 2022/03/03 18:09:33 by tsiguenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_philo(t_philo *philo, pthread_mutex_t *fork, t_data *data)
{
	pthread_mutex_t	*mutex;
	int	i;

	i = 0;
	mutex = malloc(sizeof(pthread_mutex_t));
	if (mutex == NULL)
		return (1);
	pthread_mutex_init(mutex, NULL);
	pthread_mutex_lock(mutex);
	while (i < data->nb_philo)
	{
		philo[i].mutex = mutex;
		philo[i].is_dead = 0;
		philo[i].index = i + 1;
		philo[i].fork = fork;
		philo[i].data = data;
		philo[i].last_eat = 0;
		pthread_mutex_init(&fork[i], NULL);
		pthread_create(&philo[i].thread, NULL, routine, &philo[i]);
		i++;
	}
	gettimeofday(&data->start_time, NULL);
	pthread_mutex_unlock(mutex);
	//check_death(philo, data);
	return (0);
}
