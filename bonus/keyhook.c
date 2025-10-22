/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 14:27:35 by joao-alm          #+#    #+#             */
/*   Updated: 2025/10/22 19:37:13 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fractol.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int	key_press(int key, t_fractol *ft)
{
	if (key == ESC_KEY)
		x_button(NULL);
	if (key == W_KEY)
		ft->w_press = 1;
	if (key == S_KEY)
		ft->s_press = 1;
	if (key == A_KEY)
		ft->a_press = 1;
	if (key == D_KEY)
		ft->d_press = 1;
	return (0);
}

int	key_release(int key, t_fractol *ft)
{
	if (key == W_KEY)
		ft->w_press = 0;
	if (key == S_KEY)
		ft->s_press = 0;
	if (key == A_KEY)
		ft->a_press = 0;
	if (key == D_KEY)
		ft->d_press = 0;
	return (0);
}

int	key_update(t_fractol *ft)
{
	if (ft->w_press)
		ft->offset.y -= MOVESPEED / ft->zoom;
	if (ft->s_press)
		ft->offset.y += MOVESPEED / ft->zoom;
	if (ft->a_press)
		ft->offset.x -= MOVESPEED / ft->zoom;
	if (ft->d_press)
		ft->offset.x += MOVESPEED / ft->zoom;
	if (ft->w_press || ft->s_press || ft->a_press || ft->d_press)
		draw(ft);
	return (0);
}

int	mousehook(int button, int x, int y, t_fractol *ft)
{
	(void)x;
	(void)y;
	if (button == 4)
		ft->zoom *= 1.1;
	else if (button == 5)
		ft->zoom *= 0.9;
	else
		return (1);
	ft->max_iterations = 50 + (int)(20 * log10(ft->zoom));
	if (ft->max_iterations > 1000)
		ft->max_iterations = 1000;
	draw(ft);
	return (0);
}

void	keyhook(t_fractol *ft)
{
	ft->w_press = 0;
	ft->s_press = 0;
	ft->a_press = 0;
	ft->d_press = 0;
	mlx_hook(ft->win, 17, 0, ft_exit, ft);
	mlx_hook(ft->win, 2, 1L << 0, key_press, ft);
	mlx_hook(ft->win, 3, 1L << 1, key_release, ft);
	mlx_loop_hook(ft->mlx, key_update, ft);
	mlx_mouse_hook(ft->win, mousehook, ft);
}