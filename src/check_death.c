/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsiguenz <tsiguenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 10:11:38 by tsiguenz          #+#    #+#             */
/*   Updated: 2022/03/04 12:46:59 by tsiguenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_death(t_philo *philo, t_data *data)
{
	int	i;

	while (42)
	{
		i = 0;
		pthread_mutex_lock(&philo->data->mutex);
		while (i < data->nb_philo)
		{
			if (get_time(data->start_time) - philo[i].last_eat \
				> data->time_to_die)
			{
				philo[i].is_dead = 1;
				data->stop = 1;
				printf("%ld %d %s\n", get_time(data->start_time), i + 1, M_DEAD);
				pthread_mutex_unlock(&philo->data->mutex);
				return (0);
			}
			i++;
		}
		pthread_mutex_unlock(&philo->data->mutex);
		usleep(1000);
	}
	return (0);
}

int	is_dead(t_philo *philo)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(&philo->data->mutex);
	ret = philo->data->stop;
	pthread_mutex_unlock(&philo->data->mutex);
	return (ret);
}
