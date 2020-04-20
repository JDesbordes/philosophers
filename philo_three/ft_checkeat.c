/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checkeat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacens <jacens@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 18:38:36 by jacens            #+#    #+#             */
/*   Updated: 2020/03/09 06:09:18 by jacens           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		freeforks(t_philo *philo)
{
	sem_post(philo->stats->forkmutex);
	sem_post(philo->stats->forkmutex);
	philo->nbforks = 0;
	return (0);
}

int		printeat(t_philo *philo)
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
	str = ft_strjoinrem(str, " is eating\n");
	sem_wait(philo->stats->writemutex);
	if (philo->stats->stop == 1)
	{
		sem_post(philo->stats->writemutex);
		free(str);
		return (1);
	}
	write(1, str, ft_strlen(str));
	sem_post(philo->stats->writemutex);
	sem_post(philo->stats->tabwmutex[philo->id - 1]);
	free(str);
	return (0);
}

int		ft_checkeat(t_philo *philo)
{
	if (philo->nbforks == 2)
	{
		if (printeat(philo))
			return (1);
		philo->food++;
		usleep(philo->stats->time_to_eat);
		freeforks(philo);
		return (ft_sleep(philo));
	}
	return (0);
}

void	*checker(void *data)
{
	t_philo			*philo;
	struct timeval	time;

	philo = (t_philo *)data;
	philo->food = -1;
	while (1)
	{
		sem_wait(philo->stats->tabwmutex[philo->id - 1]);
		philo->food += 1;
		gettimeofday(&time, NULL);
		philo->stats->lastfood[philo->id - 1] =
			time.tv_sec * 1000 + time.tv_usec / 1000;
		if (philo->stats->stop == 1)
			return (NULL);
	}
	return (NULL);
}
