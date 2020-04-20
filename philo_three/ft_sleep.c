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
	sem_wait(philo->stats->writemutex);
	if (philo->stats->stop == 1)
	{
		sem_post(philo->stats->writemutex);
		free(str);
		return (1);
	}
	write(1, str, ft_strlen(str));
	sem_post(philo->stats->writemutex);
	free(str);
	return (0);
}

int		ft_sleep(t_philo *philo)
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
	sem_wait(philo->stats->writemutex);
	if (philo->stats->stop == 1)
	{
		sem_post(philo->stats->writemutex);
		free(str);
		return (1);
	}
	write(1, str, ft_strlen(str));
	sem_post(philo->stats->writemutex);
	free(str);
	usleep(philo->stats->time_to_sleep);
	return (ft_think(philo));
}
