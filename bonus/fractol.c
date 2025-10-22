/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 21:13:42 by joao-alm          #+#    #+#             */
/*   Updated: 2025/10/22 19:41:10 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <X11/X.h>
#include "mlx.h"
#include "fractol.h"

void	mandelbrot(t_fractol *ft, int x, int y)
{
	t_vector	z;
	t_vector	c;
	float		temp;
	int			i;
	
	z.x = 0.0;
	z.y = 0.0;
	c.x = (x - ft->width / 2.0) / (0.5 * ft->zoom * ft->width) + ft->offset.x;
	c.y = (y - ft->height / 2.0) / (0.5 * ft->zoom * ft->height) + ft->offset.y;
	i = 0;
	while (++i <= ft->max_iterations)
	{
		temp = z.x * z.x - z.y * z.y + c.x;
		z.y = 2.0 * z.x * z.y + c.y;
		z.x = temp;
		if (z.x * z.x + z.y * z.y > 4)
			break;
	}
	int color = (int)(255.0 * i / ft->max_iterations);
	int r = (color * 9) % 256;
	int g = (color * 2) % 256;
	int b = (color * 5) % 256;
	set_pixel(&ft->img, x, y, (r << 16) | (g << 8) | b);
}

void	draw(t_fractol *ft)
{
	int	x;
	int	y;

	x = 0;
	while (++x < ft->width)
	{
		y = 0;
		while (++y < ft->height)
			ft->draw(ft, x, y);
	}
	mlx_put_image_to_window(ft->mlx, ft->win, ft->img.ptr, 0, 0);
}

int	main(int ac, char **av)
{
	t_fractol	ft;
	
	if (ac != 2)
	{
		fprintf(stderr, "error: invalid arguments\n");
		return (1);
	}
	if (strcmp(av[1], "mandelbrot") == 0)
		ft.draw = mandelbrot;
	else
	{
		fprintf(stderr, "error: choose a valid fractal:\n");
		fprintf(stderr, "- mandelbrot\n");
		return (2);
	}
	init(&ft);
	draw(&ft);
	keyhook(&ft);
	mlx_loop(ft.mlx);
	return (0);
}
