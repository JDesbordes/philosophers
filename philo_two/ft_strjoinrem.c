/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinrem.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacens <jacens@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 09:20:04 by jacens            #+#    #+#             */
/*   Updated: 2020/03/09 06:09:18 by jacens           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	*ft_strjoinrem(char const *s1, char const *s2)
{
	int		i;
	int		y;
	char	*result;

	i = ft_strlen(s1);
	y = ft_strlen(s2);
	if (!(result = malloc(sizeof(char) * (i + y + 1))))
	{
		if (s1)
			free((void *)s1);
		return (NULL);
	}
	result[i + y] = '\0';
	while (s2 && y--)
		result[i + y] = s2[y];
	while (s1 && i--)
		result[i] = s1[i];
	if (s1)
		free((void *)s1);
	return (result);
}
