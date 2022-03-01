/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsiguenz <tsiguenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 18:28:05 by tsiguenz          #+#    #+#             */
/*   Updated: 2022/03/01 16:45:07 by tsiguenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_data			data;
	t_philo			*philo;
	pthread_mutex_t	*fork;

	if (parsing(argc, argv, &data) == 1)
		return (1);
	philo = malloc(data.nb_philo * sizeof(t_philo));
	if (philo == NULL)
		return (1);
	fork = malloc(data.nb_philo * sizeof(pthread_mutex_t));
	if (fork == NULL)
		return (1);
	if (init_philo(philo, fork, &data) != 0)
		return (1);
	if (pthread_mutex_destroy(&data.mutex) != 0)
		return (1);
	free(philo);
	free(fork);
	return (0);
}
