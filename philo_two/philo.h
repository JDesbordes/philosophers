/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacens <jacens@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 07:20:07 by jacens            #+#    #+#             */
/*   Updated: 2020/03/09 06:10:55 by jacens           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdarg.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/time.h>
# include <pthread.h>
# include <semaphore.h>

typedef struct					s_file
{
	int							nb;
	long int					time_to_die;
	int							time_to_eat;
	int							time_to_sleep;
	int							max_food;
	int							option;
	int							stop;
	struct timeval				start_time;
	sem_t						*forkmutex;
	sem_t						*writemutex;
}								t_file;

typedef	struct					s_philo
{
	int							id;
	long int					lastfood;
	int							nbforks;
	int							food;
	t_file						*stats;
}								t_philo;

typedef struct					s_parent
{
	t_philo						**philo;
}								t_parent;

int								ft_atoi(const char *str);
int								ft_parse(int ac, char **av, t_file *stats);
int								ft_sleep(t_philo *philo);
char							*ft_itoa(int n);
size_t							ft_strlen(const char *str);
int								ft_dies(t_philo *philo);
char							*ft_strjoinrem(char const *s1, char const *s2);
int								ft_checkfork(t_philo *philo);
int								ft_checkeat(t_philo *philo);
int								ft_checkdeath(t_philo *philo);
void							*parent(void *data);
int								ft_free(t_philo **philo);

#endif
