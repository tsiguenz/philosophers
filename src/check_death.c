/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsiguenz <tsiguenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 10:11:38 by tsiguenz          #+#    #+#             */
/*   Updated: 2022/03/01 16:49:45 by tsiguenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_death(t_philo *philo, t_data *data)
{
	int	i;

	while (42)
	{
		i = 0;
		while (i < data->nb_philo)
		{
			if (pthread_mutex_lock(&philo[i].data->mutex) != 0)
				return (1);
			if (get_time(data->start_time) - philo[i].last_eat \
				> data->time_to_die)
			{
				philo[i].is_dead = 1;
				data->stop = 1;
				printf("%ld %d %s\n", get_time(data->start_time), i + 1, M_DEAD);
				if (pthread_mutex_unlock(&philo[i].data->mutex) != 0)
					return (1);
				return (0);
			}
			if (pthread_mutex_unlock(&philo[i].data->mutex) != 0)
				return (1);
			i++;
		}
		usleep(50);
	}
	return (0);
}
