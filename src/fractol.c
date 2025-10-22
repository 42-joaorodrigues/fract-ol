/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 21:13:42 by joao-alm          #+#    #+#             */
/*   Updated: 2025/10/22 16:49:27 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <X11/X.h>
#include "mlx.h"
#include "fractol.h"

void	draw_mandelbrot(t_fractol *ft, int x, int y)
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
		// if (z.x * z.x + z.y * z.y >= __DBL_MAX__)
		// 	break ;
	}
	// if (i >= ft->max_iterations)
	// 	my_mlx_pixel_put(&ft->img, x, y, 0x000000);
	// else
	// 	my_mlx_pixel_put(&ft->img, x, y, 0xFFFFFF);
	int color = (i * 255 / ft->max_iterations);
	set_pixel(&ft->img, x, y, (color << 16) | (color << 8) | color);
}

void	draw(t_fractol *ft)
{
	int	x;
	int	y;

	printf("draw called\n");
	x = 0;
	while (x < ft->width)
	{
		y = 0;
		while (y < ft->height)
		{
			if (y % 2 || x % 2 || y == 0 || x == 0)
				ft->draw(ft, x, y);
			else
				set_pixel(&ft->img, x, y, get_pixel(&ft->img, x - 1, y - 1));
			y += 1;
		}
		x += 1;
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
		ft.draw = draw_mandelbrot;
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
	mlx_destroy_image(ft.mlx, ft.img.ptr);
	mlx_destroy_display(ft.mlx);
	free(ft.mlx);
	return (0);
}