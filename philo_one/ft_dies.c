/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dies.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacens <jacens@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 08:38:36 by jacens            #+#    #+#             */
/*   Updated: 2020/03/09 06:09:18 by jacens           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		ft_free(t_philo **philo)
{
	free((*philo)[0].stats->forks);
	free((*philo)[0].stats);
	free(*philo);
	return (1);
}

int		ft_dies(t_philo *philo)
{
	char			*str;
	char			*str2;
	struct timeval	time;

	gettimeofday(&time, NULL);
	str = ft_itoa((time.tv_sec - philo->stats->start_time.tv_sec) * 1000 +
		(time.tv_usec - philo->stats->start_time.tv_usec) / 1000);
	str = ft_strjoinrem(str, " ");
	str2 = ft_itoa(philo->id);
	str = ft_strjoinrem(str, str2);
	free(str2);
	str = ft_strjoinrem(str, " died\n");
	pthread_mutex_lock(&philo->stats->writemutex);
	if (philo->stats->stop == 1)
	{
		pthread_mutex_unlock(&philo->stats->writemutex);
		free(str);
		return (1);
	}
	write(1, str, ft_strlen(str));
	philo->stats->stop = 1;
	pthread_mutex_unlock(&philo->stats->writemutex);
	free(str);
	return (1);
}
