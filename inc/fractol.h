/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 10:40:19 by joao-alm          #+#    #+#             */
/*   Updated: 2025/10/22 17:08:13 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
#define FRACTOL_H

#define WIN_HEIGHT 900
#define WIN_WIDTH 900

#define MOVESPEED 0.1

#define ESC_KEY 65307
#define W_KEY 119
#define A_KEY 97
#define S_KEY 115
#define D_KEY 100

typedef struct	s_vector {
	double		x;
	double		y;
}				t_vector;

typedef struct	s_img {
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
	t_vector	offset;
	int			w_press;
	int			s_press;
	int			a_press;
	int			d_press;
	int			moving;
}				t_fractol;

// fractol
void			draw(t_fractol *ft);

// keyhook
void			keyhook(t_fractol *ft);

// util
void			init(t_fractol *ft);
void			set_pixel(t_img *img, int x, int y, int color);
unsigned int	get_pixel(t_img *img, int x, int y);


#endif
