/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhook_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 10:25:16 by joao-alm          #+#    #+#             */
/*   Updated: 2025/10/28 09:51:56 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"
#include "mlx.h"
#include <math.h>
#include <stdlib.h>

// called in an mlx loop_hook, it keeps checking if enough time passed 
// without movement to draw the image in full resolution
static int	moving_update(t_fractol *ft)
{
	if (ft->moving && ft_time_ms() - ft->last_move_ms > STABLE_DELAY_MS)
	{
		ft->moving = 0;
		draw(ft);
		return (0);
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

// arrow like keys change offset
// C key changes color pallete
// activates movement boolean and draws
int	key_press(int key, t_fractol *ft)
{
	if (key == ESC_KEY)
		close_window(ft);
	else if (key == W_KEY)
		ft->offset.y -= MOVESPEED / ft->zoom;
	else if (key == S_KEY)
		ft->offset.y += MOVESPEED / ft->zoom;
	else if (key == A_KEY)
		ft->offset.x -= MOVESPEED / ft->zoom;
	else if (key == D_KEY)
		ft->offset.x += MOVESPEED / ft->zoom;
	else if (key == C_KEY)
		ft->color_shift = (ft->color_shift + 1) % 10;
	else
		return (1);
	ft->moving = 1;
	draw(ft);
	return (0);
}

// sets an offset based on the position of the mouse (mouse position zooming)
// sets moving flag, calculates max iterations based on zoom and
// draws new image
static int	mousehook(int button, int x, int y, t_fractol *ft)
{
	float		zoom_factor;
	t_vector	old;
	t_vector	new;

	if (button == 4)
		zoom_factor = 2.0;
	else if (button == 5)
		zoom_factor = 0.5;
	else
		return (1);
	old.x = (x - ft->width / 2.0) / (0.5 * ft->zoom * ft->width) + ft->offset.x;
	old.y = (y - ft->height / 2.0) / (0.5 * ft->zoom * ft->height)
		+ ft->offset.y;
	ft->zoom *= zoom_factor;
	new.x = (x - ft->width / 2.0) / (0.5 * ft->zoom * ft->width) + ft->offset.x;
	new.y = (y - ft->height / 2.0) / (0.5 * ft->zoom * ft->height)
		+ ft->offset.y;
	ft->offset.x += old.x - new.x;
	ft->offset.y += old.y - new.y;
	ft->moving = 1;
	ft->last_move_ms = ft_time_ms();
	ft->max_iterations = 50 + (int)(20 * log10(ft->zoom));
	draw(ft);
	return (0);
}

void	keyhook(t_fractol *ft)
{
	mlx_hook(ft->win, 17, 1L << 0, close_window, ft);
	mlx_hook(ft->win, 2, 1L << 0, key_press, ft);
	mlx_mouse_hook(ft->win, mousehook, ft);
	mlx_loop_hook(ft->mlx, moving_update, ft);
}
