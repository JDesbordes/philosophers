/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sleep.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacens <jacens@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 08:04:12 by jacens            #+#    #+#             */
/*   Updated: 2020/03/09 06:09:18 by jacens           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		ft_think(t_philo *philo)
{
	struct timeval	time;
	char			*str;
	char			*str2;

	gettimeofday(&time, NULL);
	str = ft_itoa((time.tv_sec - philo->stats->start_time.tv_sec) * 1000 +
		(time.tv_usec - philo->stats->start_time.tv_usec) / 1000);
	str = ft_strjoinrem(str, " ");
	str2 = ft_itoa(philo->id);
	str = ft_strjoinrem(str, str2);
	free(str2);
	str = ft_strjoinrem(str, " is thinking\n");
	pthread_mutex_lock(&philo->stats->writemutex);
	if (philo->stats->stop == 1)
	{
		pthread_mutex_unlock(&philo->stats->writemutex);
		free(str);
		return (1);
	}
	write(1, str, ft_strlen(str));
	pthread_mutex_unlock(&philo->stats->writemutex);
	free(str);
	return (0);
}

int		ft_printsleep(t_philo *philo)
{
	struct timeval	time;
	char			*str;
	char			*str2;

	gettimeofday(&time, NULL);
	str = ft_itoa((time.tv_sec - philo->stats->start_time.tv_sec) * 1000 +
		(time.tv_usec - philo->stats->start_time.tv_usec) / 1000);
	str = ft_strjoinrem(str, " ");
	str2 = ft_itoa(philo->id);
	str = ft_strjoinrem(str, str2);
	free(str2);
	str = ft_strjoinrem(str, " is sleeping\n");
	pthread_mutex_lock(&philo->stats->writemutex);
	if (philo->stats->stop == 1)
	{
		pthread_mutex_unlock(&philo->stats->writemutex);
		free(str);
		return (1);
	}
	write(1, str, ft_strlen(str));
	pthread_mutex_unlock(&philo->stats->writemutex);
	free(str);
	return (0);
}

int		ft_sleep(t_philo *philo)
{
	if (ft_printsleep(philo))
		return (1);
	if (philo->stats->time_to_eat + philo->stats->time_to_sleep >
		philo->stats->time_to_die)
	{
		usleep(philo->stats->time_to_die - philo->stats->time_to_eat);
		return (ft_dies(philo));
	}
	else
		usleep(philo->stats->time_to_sleep);
	return (ft_think(philo));
}
