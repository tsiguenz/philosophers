/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsiguenz <tsiguenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 10:11:38 by tsiguenz          #+#    #+#             */
/*   Updated: 2022/03/01 11:48:01 by tsiguenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	check_death(t_philo *philo, t_data *data)
{
	int	i;

	while (42)
	{
		i = 0;
		while (i < data->nb_philo)
		{
			if (get_time(data->start_time) - philo[i].last_eat \
				> data->time_to_die)
			{
				philo[i].is_dead = 1;
				data->stop = 1;
				p_action(get_time(data->start_time), i + 1, M_DEAD);
				return ;
			}
			i++;
		}
		usleep(50);
	}
}
