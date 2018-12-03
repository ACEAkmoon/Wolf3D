/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrushin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 19:46:43 by akrushin          #+#    #+#             */
/*   Updated: 2018/11/06 19:46:44 by akrushin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <pthread.h>
# include "libft/libft.h"

# define THREADS	8
# define TEX_SIZE	10

typedef struct		s_argb
{
	uint8_t		r;
	uint8_t		g;
	uint8_t		b;
	uint8_t		a;
}					t_argb;

typedef union		u_clr
{
	int			value;
	t_argb		argb;
}					t_clr;

typedef struct		s_set
{
	int			size;
	float		x;
	float		y;
	float		d;
	float		p;
}					t_set;

typedef struct		s_cst
{
	int			mx;
	int			my;
	t_set		set;
	float		wall;
	int			stepx;
	int			stepy;
}					t_cst;

typedef struct		s_img
{
	void		*img;
	char		*ptr;
	int			width;
	int			height;
	int			bt_px;
	int			endian;
	int			size_line;
}					t_img;

typedef struct		s_ray
{
	t_set		set;
	float		dist;
	float		light;
	int			side;
	int			tex_x;
	int			height;
	t_img		*texture;
}					t_ray;

typedef struct		s_player
{
	float		x;
	float		y;
	t_set		set;
}					t_player;

typedef struct s_map	t_map;

typedef struct		s_thread
{
	int			id;
	t_map		*map;
}					t_thread;

struct				s_map
{
	void		*mlx;
	void		*win;
	int			width;
	int			height;
	int			**arr;
	int			max_tex;
	t_ray		ray;
	t_clr		clr;
	t_list		*lst;
	t_img		*img;
	t_img		*floor;
	t_img		*ceiling;
	t_player	player;
	t_set		control;
	t_img		*tex[TEX_SIZE];
	pthread_t	pthread[THREADS];
	t_thread	threads[THREADS];
};

#endif
