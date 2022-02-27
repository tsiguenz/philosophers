/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsiguenz <tsiguenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 21:11:30 by tsiguenz          #+#    #+#             */
/*   Updated: 2022/02/27 21:59:15 by tsiguenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	get_time(long start)
{
	struct timeval	timeval;

	if (gettimeofday(&timeval, NULL) == -1)
		return (-1);
	printf("tv_usec = %ld\n", timeval.tv_usec);
	printf("start_time = %ld\n", start);
	return (timeval.tv_usec - start);
}
