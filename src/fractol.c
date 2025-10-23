/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 21:13:42 by joao-alm          #+#    #+#             */
/*   Updated: 2025/10/23 09:57:32 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "mlx.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void	mandelbrot(t_fractol *ft, int x, int y)
{
	t_vector	z;
	t_vector	c;
	float		temp;
	int			i;
	int			color;

	z.x = 0.0;
	z.y = 0.0;
	c.x = (x - ft->width / 2.0) / (0.35 * ft->zoom * ft->width) - 0.7655;
	c.y = (y - ft->height / 2.0) / (0.35 * ft->zoom * ft->height) - 0.1;
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

static void	draw(t_fractol *ft)
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

static int	mousehook(int button, int x, int y, t_fractol *ft)
{
	(void)x;
	(void)y;
	if (button == 4)
		ft->zoom *= 2.0;
	else if (button == 5)
		ft->zoom *= 0.5;
	else
		return (1);
	ft->moving = 1;
	ft->last_move_ms = ft_time_ms();
	ft->max_iterations = 50 + (int)(20 * log10(ft->zoom));
	if (ft->max_iterations > 1000)
		ft->max_iterations = 1000;
	draw(ft);
	return (0);
}

static int moving_update(t_fractol *ft)
{
    if (ft->moving && ft_time_ms() - ft->last_move_ms > STABLE_DELAY_MS)
    {
        ft->moving = 0;
        draw(ft);
    }
    return (0);
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
	mlx_hook(ft.win, 17, 0, ft_exit, &ft);
	mlx_hook(ft.win, 2, 1L << 0, esc_keypress, &ft);
	mlx_mouse_hook(ft.win, mousehook, &ft);
	mlx_loop_hook(ft.mlx, moving_update, &ft);
	mlx_loop(ft.mlx);
	return (0);
}
