/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 10:40:19 by joao-alm          #+#    #+#             */
/*   Updated: 2025/10/23 14:09:38 by joao-alm         ###   ########.fr       */
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
	t_vector	julia_c;
	int			max_iterations;
	float		zoom;
	t_vector	offset;
	int			w_press;
	int			s_press;
	int			a_press;
	int			d_press;
	int			moving;
	size_t		last_move_ms;
}				t_fractol;

// fractol
void			draw(t_fractol *ft);

// keyhook
void			keyhook(t_fractol *ft);

// util
void			init(t_fractol *ft);
size_t			ft_time_ms(void);
void			set_pixel(t_img *img, int x, int y, int color);
unsigned int	get_pixel(t_img *img, int x, int y);

#endif
