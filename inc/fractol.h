/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 10:40:19 by joao-alm          #+#    #+#             */
/*   Updated: 2025/10/23 12:44:29 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stddef.h>

# define SIZE 900
# define STABLE_DELAY_MS 200

# define ESC_KEY 65307

typedef struct s_vector
{
	float		x;
	float		y;
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
	float		julia_cx;
	float		julia_cy;
	int			max_iterations;
	float		zoom;
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
