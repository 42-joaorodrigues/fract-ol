/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 13:46:34 by joao-alm          #+#    #+#             */
/*   Updated: 2025/10/22 15:27:02 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "mlx.h"
#include "fractol.h"


void	init(t_fractol *ft)
{
	ft->mlx = mlx_init();
	ft->width = WIN_WIDTH;
	ft->height = WIN_HEIGHT;
	ft->win = mlx_new_window(ft->mlx, ft->width, ft->height,
		"fractol");
	ft->img.ptr = mlx_new_image(ft->mlx, ft->width, ft->height);
	ft->img.addr = mlx_get_data_addr(ft->img.ptr, &ft->img.bits_per_pixel,
		&ft->img.line_length, &ft->img.endian);
	ft->max_iterations = 100;
	ft->zoom = 1.0;
	ft->offset.x = 0.0;
	ft->offset.y = 0.0;
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
