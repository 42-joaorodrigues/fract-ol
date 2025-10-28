/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 10:38:22 by joao-alm          #+#    #+#             */
/*   Updated: 2025/10/28 09:24:38 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unistd.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

void	ft_putstr_fd(char *s, const int fd)
{
	if (!s)
		return ;
	while (*s)
		write(fd, s++, 1);
}

double	ft_atof(const char *str)
{
	double	res;
	double	frac;
	int		sign;
	double	div;

	res = 0;
	frac = 0;
	div = 1;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			sign = -1;
	while (*str >= '0' && *str <= '9')
		res = res * 10 + (*str++ - '0');
	if (*str++ == '.')
	{
		while (*str >= '0' && *str <= '9')
		{
			frac = frac * 10 + (*str++ - '0');
			div *= 10;
		}
	}
	return ((res + frac / div) * sign);
}
