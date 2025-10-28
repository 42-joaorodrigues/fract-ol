/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 21:13:42 by joao-alm          #+#    #+#             */
/*   Updated: 2025/10/28 09:43:35 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "helper.h"
#include "mlx.h"
#include <stdlib.h>
#include <unistd.h>

// Julia Set: zₙ₊₁ = zₙ² + c
// Each pixel (x, y) maps to complex z₀.
// c is constant for the whole image.
// Iterate until |z| > 2 or max_iterations reached.
// Color depends on how fast it escapes.
static void	julia(t_fractol *ft, int x, int y)
{
	t_vector	z;
	t_vector	c;
	long double	temp;
	int			i;
	int			color;

	z.x = (x - ft->width / 2.0) / (0.35 * ft->zoom * ft->width);
	z.y = (y - ft->height / 2.0) / (0.35 * ft->zoom * ft->height);
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
	color = (int)(255.0 * i / ft->max_iterations);
	set_pixel(&ft->img, x, y, ((color * 2) % 256 << 16) | ((color * 3)
			% 256 << 8) | (color * 4) % 256);
}

// Mandelbrot Set: zₙ₊₁ = zₙ² + c
// Each pixel (x, y) maps to complex c.
// Start with z = 0 and iterate.
// Stop when |z| > 2 or max_iterations reached.
// Color shows how quickly it diverges.
static void	mandelbrot(t_fractol *ft, int x, int y)
{
	t_vector	z;
	t_vector	c;
	long double	temp;
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

int	handle_args(int ac, char **av, t_fractol *ft)
{
	ft->julia_c.x = 0;
	ft->julia_c.y = 0;
	if (ac >= 2 && ft_strcmp(av[1], "mandelbrot") == 0)
		ft->draw = mandelbrot;
	else if (ac >= 2 && ft_strcmp(av[1], "julia") == 0)
	{
		if (ac != 4)
		{
			ft_putstr_fd("usage: julia <real> <imaginary>\n", STDERR_FILENO);
			return (1);
		}
		ft->draw = julia;
		ft->julia_c.x = ft_atof(av[2]);
		ft->julia_c.y = ft_atof(av[3]);
	}
	else
	{
		ft_putstr_fd("error: choose a valid fractal:\n", STDERR_FILENO);
		ft_putstr_fd("-> mandelbrot\n", STDERR_FILENO);
		ft_putstr_fd("-> julia <real> <imaginary>\n", STDERR_FILENO);
		return (1);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_fractol	ft;

	if (handle_args(ac, av, &ft) != 0)
		return (1);
	init(&ft);
	draw(&ft);
	keyhook(&ft);
	mlx_loop(ft.mlx);
	mlx_destroy_image(ft.mlx, ft.img.ptr);
	mlx_destroy_window(ft.mlx, ft.win);
	mlx_destroy_display(ft.mlx);
	free(ft.mlx);
	return (0);
}
