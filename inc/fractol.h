/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 10:40:19 by joao-alm          #+#    #+#             */
/*   Updated: 2025/10/23 08:56:56 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# define SIZE 900
# define MOVESPEED 0.1
# define ESC_KEY 65307

typedef struct s_vector
{
	double		x;
	double		y;
}				t_vector;

typedef struct s_img
{
	void		*ptr;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_img;

typedef struct s_fractol
{
	void		*mlx;
	void		*win;
	t_img		img;
	int			width;
	int			height;
	void		(*draw)(struct s_fractol *ft, int x, int y);
	int			max_iterations;
	double		zoom;
}				t_fractol;

// util
void			init(t_fractol *ft);
int				ft_exit(t_fractol *ft);
int				esc_keypress(int key, t_fractol *ft);
void			set_pixel(t_img *img, int x, int y, int color);

#endif
