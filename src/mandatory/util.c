/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 13:46:34 by joao-alm          #+#    #+#             */
/*   Updated: 2025/10/24 11:26:34 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>

void	init(t_fractol *ft)
{
	ft->mlx = mlx_init();
	ft->width = SIZE;
	ft->height = SIZE;
	ft->win = mlx_new_window(ft->mlx, ft->width, ft->height, "fractol");
	ft->img.ptr = mlx_new_image(ft->mlx, ft->width, ft->height);
	ft->img.addr = mlx_get_data_addr(ft->img.ptr, &ft->img.bits_per_pixel,
			&ft->img.line_length, &ft->img.endian);
	if (ft->julia_c.x > 2.0)
		ft->julia_c.x = 2.0;
	if (ft->julia_c.x < -2.0)
		ft->julia_c.x = -2.0;
	if (ft->julia_c.y > 2.0)
		ft->julia_c.y = 2.0;
	if (ft->julia_c.y < -2.0)
		ft->julia_c.y = 2.0;
	ft->zoom = 1.0;
	ft->max_iterations = 50 + (int)(20 * log10(ft->zoom));
	ft->moving = 0;
}

size_t	ft_time_ms(void)
{
	struct timeval	tv;
	size_t			seconds;
	size_t			microseconds;

	gettimeofday(&tv, NULL);
	seconds = tv.tv_sec;
	microseconds = tv.tv_usec;
	return (seconds * 1000 + microseconds / 1000);
}

void	set_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

unsigned int	get_pixel(t_img *img, int x, int y)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}
