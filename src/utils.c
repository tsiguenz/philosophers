/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsiguenz <tsiguenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 16:35:58 by tsiguenz          #+#    #+#             */
/*   Updated: 2022/03/04 16:36:51 by tsiguenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	get_time(struct timeval start)
{
	struct timeval	now;

	if (gettimeofday(&now, NULL) == -1)
		return (-1);
	return ((now.tv_sec * 1000 + now.tv_usec / 1000) - \
			(start.tv_sec * 1000 + start.tv_usec / 1000));
}

void	p_action(t_philo *philo, char *message)
{
	pthread_mutex_lock(&philo->data->mutex);
	if (philo->data->stop == 0 && philo->data->stop == 0)
		printf("%ld %d %s\n", get_time(philo->data->start_time), philo->index, \
		message);
	pthread_mutex_unlock(&philo->data->mutex);
}
