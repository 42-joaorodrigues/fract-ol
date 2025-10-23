/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 13:46:34 by joao-alm          #+#    #+#             */
/*   Updated: 2025/10/23 08:57:29 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "mlx.h"
#include <stdio.h>
#include <stdlib.h>

void	init(t_fractol *ft)
{
	ft->mlx = mlx_init();
	ft->width = SIZE;
	ft->height = SIZE;
	ft->win = mlx_new_window(ft->mlx, ft->width, ft->height, "fractol");
	ft->img.ptr = mlx_new_image(ft->mlx, ft->width, ft->height);
	ft->img.addr = mlx_get_data_addr(ft->img.ptr, &ft->img.bits_per_pixel,
			&ft->img.line_length, &ft->img.endian);
	ft->max_iterations = 100;
	ft->zoom = 1.0;
}

int	ft_exit(t_fractol *ft)
{
	mlx_destroy_image(ft->mlx, ft->img.ptr);
	mlx_destroy_display(ft->mlx);
	free(ft->mlx);
	exit(0);
	return (0);
}

int	esc_keypress(int key, t_fractol *ft)
{
	if (key == ESC_KEY)
		ft_exit(ft);
	return (0);
}

void	set_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
