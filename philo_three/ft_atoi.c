/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacens <jacens@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 13:44:30 by jacens            #+#    #+#             */
/*   Updated: 2020/03/09 06:09:18 by jacens           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t			ft_strlen(const char *str)
{
	size_t		i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		i++;
	}
	return (i);
}

int				ft_atoi(const char *str)
{
	int			i;
	int			sign;
	long int	answer;

	answer = 0;
	sign = 1;
	i = 0;
	if (!str)
		return (0);
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\f'
			|| str[i] == '\v' || str[i] == '\r' || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] != '\0' && (str[i] >= '0' && str[i] <= '9'))
	{
		answer = answer * 10 + (str[i] - '0');
		i++;
	}
	return (answer * sign);
}

static int		ft_recursive_power(int nb, int power)
{
	power--;
	if (power == -1)
		return (1);
	else if (power < 0)
		return (0);
	else if (power >= 0)
		return (nb * ft_recursive_power(nb, power));
	return (0);
}

static char		*otheritoa(long n, int size, int sign)
{
	char *result;
	long i;

	i = n;
	while (i >= 10)
	{
		i /= 10;
		size++;
	}
	if (!(result = malloc(sizeof(char) * (size + 2))))
		return (NULL);
	result[0] = '-';
	i = size;
	size = sign > 0 ? size : size - 1;
	while (size >= 0)
	{
		result[i - size] = '0' + (n / ft_recursive_power(10, size));
		n -= (n / ft_recursive_power(10, size)) * ft_recursive_power(10, size);
		size--;
	}
	result[i + 1] = '\0';
	return (result);
}

char			*ft_itoa(int n)
{
	long	n2;
	int		size;
	int		sign;

	n2 = n;
	size = 0;
	sign = 1;
	if (n2 < 0)
	{
		n2 *= -1;
		size++;
		sign = -1;
	}
	return (otheritoa(n2, size, sign));
}
