/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 21:13:42 by joao-alm          #+#    #+#             */
/*   Updated: 2025/10/23 11:13:22 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void	julia(t_fractol *ft, int x, int y)
{
	t_vector	z;
	t_vector	c;
	float		temp;
	int			i;
	int			color;

	z.x = (x - ft->width / 2.0) / (0.35 * ft->zoom * ft->width);
	z.y = (y - ft->height / 2.0) / (0.35 * ft->zoom * ft->height);
	c.x = -0.766;
	c.y = -0.0999;
	i = 0;
	while (++i <= ft->max_iterations)
	{
		temp = z.x * z.x - z.y * z.y + c.x;
		z.y = 2.0 * z.x * z.y + c.y;
		z.x = temp;
		if (z.x * z.x + z.y * z.y > 4)
			break ;
	}
	color = (int)(255.0 * i / ft->max_iterations);
	set_pixel(&ft->img, x, y, ((color * 2) % 256 << 16) | ((color *9)
			% 256 << 8) | (color * 3) % 256);
}

static void	mandelbrot(t_fractol *ft, int x, int y)
{
	t_vector	z;
	t_vector	c;
	float		temp;
	int			i;
	int			color;

	z.x = 0.0;
	z.y = 0.0;
	c.x = (x - ft->width / 2.0) / (0.35 * ft->zoom * ft->width) - 0.766;
	c.y = (y - ft->height / 2.0) / (0.35 * ft->zoom * ft->height) - 0.0999;
	i = 0;
	while (++i <= ft->max_iterations)
	{
		temp = z.x * z.x - z.y * z.y + c.x;
		z.y = 2.0 * z.x * z.y + c.y;
		z.x = temp;
		if (z.x * z.x + z.y * z.y > 4)
			break ;
	}
	color = (int)(255.0 * i / ft->max_iterations);
	set_pixel(&ft->img, x, y, ((color * 9) % 256 << 16) | ((color * 2)
			% 256 << 8) | (color * 5) % 256);
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

int	main(int ac, char **av)
{
	t_fractol	ft;

	if (ac != 2 || (strcmp(av[1], "mandelbrot") != 0 && strcmp(av[1],
				"julia") != 0))
	{
		fprintf(stderr, "error: choose a valid fractal:\n");
		fprintf(stderr, "- mandelbrot\n- julia\n");
		return (1);
	}
	ft.draw = mandelbrot;
	if (strcmp(av[1], "julia") == 0)
		ft.draw = julia;
	init(&ft);
	draw(&ft);
	keyhook(&ft);
	mlx_loop(ft.mlx);
	mlx_destroy_image(ft.mlx, ft.img.ptr);
	mlx_destroy_display(ft.mlx);
	free(ft.mlx);
	return (0);
}
