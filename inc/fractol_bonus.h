/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 10:40:19 by joao-alm          #+#    #+#             */
/*   Updated: 2025/10/24 11:36:12 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_BONUS_H
# define FRACTOL_BONUS_H

# include <stddef.h>

# define SIZE 900
# define MOVESPEED 0.5
# define STABLE_DELAY_MS 200

# define ESC_KEY 65307
# define W_KEY 119
# define S_KEY 115
# define A_KEY 97
# define D_KEY 100
# define C_KEY 99

typedef struct s_vector
{
	long double	x;
	long double	y;
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
	t_vector	julia_c;
	int			max_iterations;
	float		zoom;
	t_vector	offset;
	int			moving;
	size_t		last_move_ms;
	int			color_shift;
}				t_fractol;

// fractals
void			burning_ship(t_fractol *ft, int x, int y);
void			julia(t_fractol *ft, int x, int y);
void			mandelbrot(t_fractol *ft, int x, int y);

// fractol
void			draw(t_fractol *ft);

// keyhook
void			keyhook(t_fractol *ft);

// util
void			init(t_fractol *ft);
size_t			ft_time_ms(void);
unsigned int	get_color(t_fractol *ft, int i, int flame);
void			set_pixel(t_img *img, int x, int y, int color);
unsigned int	get_pixel(t_img *img, int x, int y);

#endif
