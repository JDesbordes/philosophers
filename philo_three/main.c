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
	usleep((start_time.tv_usec % 100) * 55);
	while (1)
	{
		ft_checkfork(philo);
	}
	return (NULL);
}

int		ft_unlink(t_file *stats)
{
	int		i;
	char	*str;

	i = 0;
	sem_unlink("forks");
	sem_unlink("writes");
	while (i < stats->nb)
	{
		str = ft_itoa(i);
		sem_unlink(str);
		free(str);
		i++;
	}
	return (1);
}

int		threading(t_philo *philo, int i, t_parent papa)
{
	int			j;
	int			rc;
	pthread_t	threads[i + 1];

	j = 0;
	while (j < i)
	{
		rc = pthread_create(&threads[j], NULL, checker, &(philo[j]));
		if (rc)
			return (write(1, "THREAD ERROR\n", 14));
		j++;
	}
	rc = pthread_create(&threads[i], NULL, parent, &papa);
	if (rc)
		return (write(1, "THREAD ERROR\n", 14));
	j = 0;
	pthread_join(threads[i], NULL);
	while (j < i)
	{
		pthread_join(threads[j], NULL);
		j++;
	}
	return (0);
}

int		philo1(int ac, char **av, int i)
{
	t_file		*stats;
	t_philo		*philo;
	pid_t		info;
	t_parent	papa;
	int			j;

	stats = malloc(sizeof(t_file) * 1);
	if (!ft_parse(ac, av, stats))
		return (0);
	if (!(philo = initphilo(i, stats)))
		return (0);
	papa.philo = &philo;
	j = 0;
	while (j < i)
	{
		info = fork();
		if (info == 0)
			cycle((void *)&(philo[j]));
		stats->forks[j] = info;
		j++;
	}
	if (threading(philo, i, papa))
		return (0);
	ft_unlink(stats);
	return (ft_free(&philo));
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
