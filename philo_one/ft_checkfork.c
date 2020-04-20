/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checkfork.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacens <jacens@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 11:21:31 by jacens            #+#    #+#             */
/*   Updated: 2020/03/09 06:09:18 by jacens           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int			printfork(t_philo *philo)
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
	str = ft_strjoinrem(str, " has taken a fork\n");
	pthread_mutex_lock(&philo->stats->writemutex);
	if (philo->stats->stop == 1)
	{
		pthread_mutex_unlock(&philo->stats->writemutex);
		pthread_mutex_unlock(&philo->stats->forkmutex);
		free(str);
		return (1);
	}
	write(1, str, ft_strlen(str));
	pthread_mutex_unlock(&philo->stats->writemutex);
	free(str);
	return (0);
}

static int	ft_checkfork_if(t_philo *philo)
{
	if (philo->id == philo->stats->nb)
	{
		if (philo->stats->forks[0])
		{
			if (printfork(philo))
				return (1);
			philo->stats->forks[0] = 0;
			philo->nbforks += 1;
		}
	}
	else if (philo->stats->forks[philo->id])
	{
		if (printfork(philo))
			return (1);
		philo->stats->forks[philo->id] = 0;
		philo->nbforks += 1;
	}
	return (0);
}

int			ft_checkfork(t_philo *philo)
{
	pthread_mutex_lock(&philo->stats->forkmutex);
	if (philo->stats->forks[philo->id - 1])
	{
		if (printfork(philo))
			return (1);
		philo->stats->forks[philo->id - 1] = 0;
		philo->nbforks += 1;
	}
	pthread_mutex_unlock(&philo->stats->forkmutex);
	pthread_mutex_lock(&philo->stats->forkmutex);
	if (ft_checkfork_if(philo))
		return (1);
	pthread_mutex_unlock(&philo->stats->forkmutex);
	if (ft_checkeat(philo))
		return (1);
	return (0);
}
