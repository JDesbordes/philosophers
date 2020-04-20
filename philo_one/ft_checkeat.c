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

int			freeforks(t_philo *philo)
{
	if (philo->id == philo->stats->nb)
	{
		philo->stats->forks[0] = 1;
		philo->stats->forks[philo->id - 1] = 1;
	}
	else
	{
		philo->stats->forks[philo->id - 1] = 1;
		philo->stats->forks[philo->id] = 1;
	}
	philo->nbforks = 0;
	return (0);
}

static int	ft_check_val_more(t_philo *philo)
{
	if (philo->stats->max_food > 0 && philo->food >= philo->stats->max_food)
	{
		pthread_mutex_lock(&philo->stats->writemutex);
		if (philo->stats->stop == 1)
		{
			pthread_mutex_unlock(&philo->stats->writemutex);
			return (1);
		}
		write(1, "philo is satiatied\n", 20);
		pthread_mutex_unlock(&philo->stats->writemutex);
		philo->stats->stop = 1;
		return (1);
	}
	if (philo->stats->time_to_eat >= philo->stats->time_to_die)
	{
		usleep(philo->stats->time_to_die);
		return (ft_dies(philo));
	}
	else
		usleep(philo->stats->time_to_eat);
	freeforks(philo);
	if (ft_sleep(philo))
		return (1);
	return (0);
}

static int	ft_check_val(t_philo *philo, int ret)
{
	struct timeval	time;
	char			*str;
	char			*str2;

	gettimeofday(&time, NULL);
	philo->lastfood = time.tv_sec * 1000 + time.tv_usec / 1000;
	str = ft_itoa((time.tv_sec - philo->stats->start_time.tv_sec) *
	1000 + (time.tv_usec - philo->stats->start_time.tv_usec) / 1000);
	str = ft_strjoinrem(str, " ");
	str2 = ft_itoa(philo->id);
	str = ft_strjoinrem(str, str2);
	free(str2);
	str = ft_strjoinrem(str, " is eating\n");
	pthread_mutex_lock(&philo->stats->writemutex);
	if (philo->stats->stop == 1)
	{
		free(str);
		return (!pthread_mutex_unlock(&philo->stats->writemutex));
	}
	write(1, str, ft_strlen(str));
	pthread_mutex_unlock(&philo->stats->writemutex);
	free(str);
	philo->food++;
	ret = ft_check_val_more(philo);
	return (ret);
}

int			ft_checkeat(t_philo *philo)
{
	if (philo->nbforks == 2)
	{
		if (ft_check_val(philo, 0))
			return (1);
	}
	else
	{
		if (ft_checkdeath(philo))
			return (1);
	}
	return (0);
}
