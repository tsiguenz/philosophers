/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsiguenz <tsiguenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 15:01:06 by tsiguenz          #+#    #+#             */
/*   Updated: 2022/03/04 12:45:01 by tsiguenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	destroy_philo(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
}

static void	destroy_fork(t_data *data, pthread_mutex_t *fork)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&fork[i]);
		i++;
	}
}

int	ft_free(void *philo, void *fork)
{
	free(philo);
	free(fork);
	return (1);
}

int	ft_exit(t_data *data, t_philo *philo, pthread_mutex_t *fork)
{

	destroy_philo(data, philo);
	destroy_fork(data, fork);
	pthread_mutex_destroy(&data->mutex);
	ft_free(philo, fork);
	return (0);
}
