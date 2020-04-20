/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacens <jacens@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 07:43:20 by jacens            #+#    #+#             */
/*   Updated: 2020/03/09 06:09:18 by jacens           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		ft_check(int ac, t_file *stats)
{
	if (stats->nb < 1)
	{
		write(1, "Need at least one philosopher\n", 30);
		return (0);
	}
	if (stats->time_to_die <= 0)
	{
		write(1, "philosophers start dead\n", 25);
		return (0);
	}
	if (stats->time_to_eat < 0 || stats->time_to_sleep < 0)
	{
		write(1, "negative time_to_eat or time_to_sleep\n", 38);
		return (0);
	}
	if (ac == 6 && stats->max_food < 1)
	{
		write(1, "philosophers start satiated\n", 28);
		return (0);
	}
	return (1);
}

int		ft_deadsems(t_file *stats)
{
	int		i;
	char	*str;
	sem_t	*writemutex;

	i = 0;
	if (!(stats->tabwmutex = malloc(sizeof(sem_t *) * stats->nb)))
		return (0);
	while (i < stats->nb)
	{
		str = ft_itoa(i);
		writemutex = sem_open(str, O_CREAT, 0660, 1);
		stats->tabwmutex[i] = writemutex;
		free(str);
		i++;
	}
	if (!(stats->forks = (pid_t *)(malloc(sizeof(pid_t) * stats->nb))))
		return (0);
	if (!(stats->lastfood = (long int *)(malloc(sizeof(long int) * stats->nb))))
		return (0);
	return (1);
}

int		ft_parse(int ac, char **av, t_file *stats)
{
	stats->option = 0;
	stats->stop = 0;
	stats->nb = ft_atoi(av[1]);
	stats->time_to_die = (long int)ft_atoi(av[2]) * 1000;
	stats->time_to_eat = ft_atoi(av[3]) * 1000;
	stats->time_to_sleep = ft_atoi(av[4]) * 1000;
	gettimeofday(&stats->start_time, NULL);
	stats->forkmutex = sem_open("forks", O_CREAT, 0660, stats->nb);
	stats->writemutex = sem_open("writes", O_CREAT, 0660, 1);
	if (!ft_deadsems(stats))
		return (0);
	if (ac == 6)
	{
		stats->max_food = ft_atoi(av[5]);
		if (stats->max_food < 1)
		{
			write(1, "philosophers start satiated\n", 28);
			return (0);
		}
	}
	else
		stats->max_food = -1;
	return (ft_check(ac, stats));
}

t_philo	*initphilo(int i, t_file *stats)
{
	int			j;
	t_philo		*philo;

	if (!(philo = (t_philo *)(malloc(sizeof(t_philo) * i))))
		return (NULL);
	j = 0;
	while (j < i)
	{
		philo[j].id = j + 1;
		philo[j].stats = stats;
		philo[j].nbforks = 0;
		philo[j].food = 0;
		j++;
	}
	return (philo);
}

int		ft_free(t_philo **philo)
{
	free((*philo)[0].stats->lastfood);
	free((*philo)[0].stats->forks);
	free((*philo)[0].stats->tabwmutex);
	free((*philo)[0].stats);
	free(*philo);
	return (1);
}
