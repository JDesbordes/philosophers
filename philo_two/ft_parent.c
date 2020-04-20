/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parent.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacens <jacens@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 13:57:45 by jacens            #+#    #+#             */
/*   Updated: 2020/03/09 06:09:18 by jacens           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void			addmutexes(t_philo *philo)
{
	int		i;

	i = 0;
	sem_post(philo->stats->writemutex);
	while (i < philo->stats->nb)
	{
		sem_post(philo->stats->forkmutex);
		i++;
	}
}

int				ft_checkdeath(t_philo *philo)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	if ((time.tv_sec * 1000 + time.tv_usec / 1000) - philo->lastfood >
		philo->stats->time_to_die / 1000)
	{
		ft_dies(philo);
		addmutexes(philo);
		return (1);
	}
	else if (philo->stats->max_food > 0 && philo->food >=
		philo->stats->max_food)
	{
		sem_wait(philo->stats->writemutex);
		if (philo->stats->stop == 1)
		{
			sem_post(philo->stats->writemutex);
			return (1);
		}
		write(1, "philo is satiatied\n", 20);
		philo->stats->stop = 1;
		addmutexes(philo);
		return (1);
	}
	return (0);
}

int				ft_dies(t_philo *philo)
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
	sem_wait(philo->stats->writemutex);
	if (philo->stats->stop == 1)
	{
		sem_post(philo->stats->writemutex);
		free(str);
		return (1);
	}
	write(1, str, ft_strlen(str));
	philo->stats->stop = 1;
	sem_post(philo->stats->writemutex);
	free(str);
	return (1);
}

void			*parent(void *data)
{
	t_parent	*papa;
	t_philo		**philo;
	int			i;

	papa = (t_parent *)data;
	philo = (*papa).philo;
	usleep(1000);
	while (1)
	{
		i = 0;
		while (i < (*philo)[0].stats->nb)
		{
			if (ft_checkdeath(&((*philo)[i])))
			{
				return (NULL);
			}
			i++;
		}
	}
	return (NULL);
}

int				ft_free(t_philo **philo)
{
	free((*philo)[0].stats);
	free(*philo);
	return (1);
}
