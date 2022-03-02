/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsiguenz <tsiguenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 15:01:06 by tsiguenz          #+#    #+#             */
/*   Updated: 2022/03/02 15:22:51 by tsiguenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	destroy_philo(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_join(philo[i].thread, NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

static int	destroy_fork(t_data *data, pthread_mutex_t *fork)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_mutex_destroy(&fork[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	ft_free(t_philo *philo, pthread_mutex_t *fork)
{
	free(philo);
	free(fork);
	return (1);
}

int	ft_exit(t_data *data, t_philo *philo, pthread_mutex_t *fork)
{
	if (destroy_philo(data, philo) == 1)
		return (ft_free(philo, fork));
	if(destroy_fork(data, fork) == 1)
		return (ft_free(philo, fork));
	if (pthread_mutex_destroy(&data->mutex) != 0)
		return (ft_free(philo, fork));
	ft_free(philo, fork);
	return (0);
}
