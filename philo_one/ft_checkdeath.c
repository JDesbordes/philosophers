/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checkdeath.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacens <jacens@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 19:09:20 by jacens            #+#    #+#             */
/*   Updated: 2020/03/09 06:09:18 by jacens           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		ft_checkdeath(t_philo *philo)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	if ((time.tv_sec * 1000 + time.tv_usec / 1000) - philo->lastfood >
	philo->stats->time_to_die / 1000)
	{
		ft_dies(philo);
		return (1);
	}
	return (0);
}
