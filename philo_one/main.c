/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacens <jacens@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 07:19:46 by jacens            #+#    #+#             */
/*   Updated: 2020/03/09 06:09:18 by jacens           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*cycle(void *strct)
{
	t_philo			*philo;
	struct timeval	start_time;

	philo = (t_philo *)strct;
	gettimeofday(&start_time, NULL);
	usleep(start_time.tv_usec % 10);
	philo->lastfood = (start_time.tv_sec) * 1000 + (start_time.tv_usec) / 1000;
	while (1)
	{
		if (ft_checkfork(philo))
			return (NULL);
	}
	return (NULL);
}

void	initphilo(t_philo **philo, int i, t_file *stats)
{
	int	j;

	j = 0;
	while (j < i)
	{
		(*philo)[j].id = j + 1;
		(*philo)[j].stats = stats;
		(*philo)[j].nbforks = 0;
		(*philo)[j].food = 0;
		j++;
	}
}

int		philo1(int ac, char **av, int i)
{
	t_file		*stats;
	t_philo		*philo;
	pthread_t	threads[i];
	int			j;
	int			rc;

	stats = malloc(sizeof(t_file) * 1);
	if (!(philo = (t_philo *)(malloc(sizeof(t_philo) * i))))
		return (1);
	if (!ft_parse(ac, av, stats))
		return (1);
	initphilo(&philo, i, stats);
	j = 0;
	while (j < i)
	{
		rc = pthread_create(&threads[j], NULL, cycle, &(philo[j]));
		if (rc)
			return (write(1, "THREAD ERROR\n", 14));
		j++;
	}
	j = -1;
	while (++j < i)
		pthread_join(threads[j], NULL);
	ft_free(&philo);
	return (1);
}

int		main(int ac, char **av)
{
	int nb;

	nb = ft_atoi(av[1]);
	if (ac != 5 && ac != 6)
	{
		write(1, "Needs 4/5 arguments\n", 20);
		return (0);
	}
	else
		philo1(ac, av, nb);
	return (0);
}
