/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 18:20:00 by joao-alm          #+#    #+#             */
/*   Updated: 2025/10/24 11:38:11 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"
#include "mlx.h"
#include <math.h>

void	burning_ship(t_fractol *ft, int x, int y)
{
	t_vector	z;
	t_vector	c;
	long double	temp;
	int			i;

	z.x = 0;
	z.y = 0;
	c.x = (x - ft->width / 2.0) / (0.35 * ft->zoom * ft->width)
		- 0.4 + ft->offset.x;
	c.y = (y - ft->height / 2.0) / (0.35 * ft->zoom * ft->height)
		- 0.5 + ft->offset.y;
	i = 0;
	while (++i <= ft->max_iterations)
	{
		temp = z.x * z.x - z.y * z.y + c.x;
		z.y = fabsl(2.0 * z.x * z.y) + c.y;
		z.x = fabsl(temp);
		if (z.x * z.x + z.y * z.y > 4)
			break ;
	}
	if (i >= ft->max_iterations)
		set_pixel(&ft->img, x, y, 0x000000);
	else
		set_pixel(&ft->img, x, y, get_color(ft, i, 1));
}

void	julia(t_fractol *ft, int x, int y)
{
	t_vector	z;
	t_vector	c;
	long double	temp;
	int			i;

	z.x = (x - ft->width / 2.0) / (0.35 * ft->zoom * ft->width)
		+ ft->offset.x;
	z.y = (y - ft->height / 2.0) / (0.35 * ft->zoom * ft->height)
		+ ft->offset.y;
	c.x = ft->julia_c.x;
	c.y = ft->julia_c.y;
	i = 0;
	while (++i <= ft->max_iterations)
	{
		temp = z.x * z.x - z.y * z.y + c.x;
		z.y = 2.0 * z.x * z.y + c.y;
		z.x = temp;
		if (z.x * z.x + z.y * z.y > 4)
			break ;
	}
	if (i >= ft->max_iterations)
		set_pixel(&ft->img, x, y, 0x000000);
	else
		set_pixel(&ft->img, x, y, get_color(ft, i, 0));
}

void	mandelbrot(t_fractol *ft, int x, int y)
{
	t_vector	z;
	t_vector	c;
	long double	temp;
	int			i;

	z.x = 0.0;
	z.y = 0.0;
	c.x = (x - ft->width / 2.0) / (0.35 * ft->zoom * ft->width)
		- 0.766 + ft->offset.x;
	c.y = (y - ft->height / 2.0) / (0.35 * ft->zoom * ft->height)
		- 0.0999 + ft->offset.y;
	i = 0;
	while (++i <= ft->max_iterations)
	{
		temp = z.x * z.x - z.y * z.y + c.x;
		z.y = 2.0 * z.x * z.y + c.y;
		z.x = temp;
		if (z.x * z.x + z.y * z.y > 4)
			break ;
	}
	if (i >= ft->max_iterations)
		set_pixel(&ft->img, x, y, 0x000000);
	else
		set_pixel(&ft->img, x, y, get_color(ft, i, 0));
}

void	draw(t_fractol *ft)
{
	int	x;
	int	y;

	x = -1;
	while (++x < ft->width)
	{
		y = -1;
		while (++y < ft->height)
		{
			if (ft->moving && x != 0 && x & 1)
				set_pixel(&ft->img, x, y, get_pixel(&ft->img, x - 1, y));
			else
				ft->draw(ft, x, y);
		}
	}
	mlx_put_image_to_window(ft->mlx, ft->win, ft->img.ptr, 0, 0);
}
