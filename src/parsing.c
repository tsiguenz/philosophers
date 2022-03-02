/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsiguenz <tsiguenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 18:55:21 by tsiguenz          #+#    #+#             */
/*   Updated: 2022/03/02 16:38:27 by tsiguenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	ft_atoi(char *str)
{
	int		i;
	long	ret;

	i = 0;
	ret = 0;
	while (*str == '0')
		str++;
	while (str[i])
	{
		ret = ret * 10 + str[i] - '0';
		i++;
	}
	if (i > 10 || ret > INT_MAX)
		return (-1);
	return ((int) ret);
}

static int	is_formated(int argc, char **argv)
{
	int	i;
	int	y;

	i = 1;
	while (i < argc)
	{
		y = 0;
		if (argv[i][y] == '\0' || (argv[i][y] == '0' && argv[i][y + 1] == '\0'))
			return (0);
		while (argv[i][y])
		{
			if (argv[i][y] < '0' || argv[i][y] > '9')
				return (0);
			y++;
		}
		i++;
	}
	return (1);
}

static int	set_data(int argc, char **argv, t_data *data)
{
	data->nb_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->iteration = 0;
	if (argc == 6)
		data->iteration = ft_atoi(argv[5]);
	data->stop = 0;
	return (0);
}

int	parsing(int argc, char **argv, t_data *data)
{
	if (argc != 5 && argc != 6)
		return (1);
	if (is_formated(argc, argv) == 0)
		return (1);
	if (set_data(argc, argv, data) == 1)
		return (1);
	if (data->nb_philo == -1)
		return (1);
	if (data->time_to_die == -1)
		return (1);
	if (data->time_to_eat == -1)
		return (1);
	if (data->time_to_sleep == -1)
		return (1);
	if (data->iteration == -1)
		return (1);
	return (0);
}
