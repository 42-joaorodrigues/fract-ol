/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 21:13:42 by joao-alm          #+#    #+#             */
/*   Updated: 2025/10/24 11:30:28 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"
#include "helper.h"
#include "mlx.h"
#include <stdlib.h>
#include <unistd.h>

int	handle_args(int ac, char **av, t_fractol *ft)
{
	ft->julia_c.x = 0;
	ft->julia_c.y = 0;
	if (ac >= 2 && ft_strcmp(av[1], "mandelbrot") == 0)
		ft->draw = mandelbrot;
	else if (ac >= 2 && ft_strcmp(av[1], "burning_ship") == 0)
		ft->draw = burning_ship;
	else if (ac >= 2 && ft_strcmp(av[1], "julia") == 0)
	{
		if (ac != 4)
			return (ft_putstr_fd("usage: julia <real> <imaginary>\n",
					STDERR_FILENO), 1);
		ft->draw = julia;
		ft->julia_c.x = ft_atof(av[2]);
		ft->julia_c.y = ft_atof(av[3]);
	}
	else
	{
		ft_putstr_fd("error: choose a valid fractal:\n", STDERR_FILENO);
		ft_putstr_fd("-> mandelbrot\n", STDERR_FILENO);
		ft_putstr_fd("-> julia <real> <imaginary>\n", STDERR_FILENO);
		ft_putstr_fd("-> burning_ship\n", STDERR_FILENO);
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
