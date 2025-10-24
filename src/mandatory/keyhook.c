/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 10:25:16 by joao-alm          #+#    #+#             */
/*   Updated: 2025/10/24 11:26:15 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "mlx.h"
#include <stdlib.h>
#include <math.h>

static int	moving_update(t_fractol *ft)
{
	if (ft->moving && ft_time_ms() - ft->last_move_ms > STABLE_DELAY_MS)
	{
		ft->moving = 0;
		draw(ft);
	}
	return (0);
}

static int	close_window(t_fractol *ft)
{
	mlx_destroy_image(ft->mlx, ft->img.ptr);
	mlx_destroy_window(ft->mlx, ft->win);
	mlx_destroy_display(ft->mlx);
	free(ft->mlx);
	exit(0);
	return (0);
}

static int	esc_keypress(int key, t_fractol *ft)
{
	if (key == ESC_KEY)
		close_window(ft);
	return (0);
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
	draw(ft);
	return (0);
}

void	keyhook(t_fractol *ft)
{
	mlx_hook(ft->win, 17, 1L << 0, close_window, ft);
	mlx_hook(ft->win, 2, 1L << 0, esc_keypress, ft);
	mlx_mouse_hook(ft->win, mousehook, ft);
	mlx_loop_hook(ft->mlx, moving_update, ft);
}
