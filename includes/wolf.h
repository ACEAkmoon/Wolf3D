/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrushin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 18:16:56 by akrushin          #+#    #+#             */
/*   Updated: 2018/10/23 18:16:58 by akrushin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H

# include <math.h>
# include <stdint.h>
# include "structs.h"
# include "libft/libft.h"
# include <minilibx/mlx.h>

# define NAME				"Project - Wolf3D"
# define SRC_TILES			"data_files/textures/"
# define SRC_SOUNDS			"data_files/sounds/"

# define INF_CLR			0xBCA6A0
# define MINI_MAP_CLR		0xF8F8F8
# define SIGHT_CLR			0x0057E5
# define WALLS_CLR			0x000000
# define FLOOR_CLR			0x01011A
# define CEILING_CLR		0x000000

# define NOC				\033[0m
# define OKC				\033[32m
# define ERC				\033[31m
# define WAC				\033[33m
# define TSC				\033[94;1m

# define WIN_W 				1440
# define WIN_H 				900
# define TOP_MRGN			5
# define LFT_MRGN			10
# define ZOOM 				1.1f
# define ANGLE 				180.0f
# define SPEED_MOVE			0.1f
# define SPEED_TURN			5.0f
# define VIEW_DIST			50

# define ESC				53
# define CTRL				59
# define KEY_C				8
# define KEY_L				37
# define UP					126
# define DOWN				125
# define LEFT				123
# define RIGHT				124
# define P_UP				116
# define P_DOWN				121
# define NUM_0				82
# define NUM_1				83
# define NUM_DIV			75
# define NUM_MULT			67
# define NUM_PLUS			69
# define NUM_MINUS			78
# define NUM_ENTER			76
# define SCROLL_UP			4
# define SCROLL_DOWN		5

# define MAP_DELL(x, map)	if (x) ft_map_clean(map);
# define ERROR(x, message) 	if (x) ft_error(message);
# define CLEAN(x, list)		if (x) ft_lst_clean(list);
# define EXIT_MASSAGE()		ft_putendl("\033[33mExit Wolf3D\033[0m");
# define SOUND_OFF()		system("killall afplay 2&>/dev/null >/dev/null");

int			ft_remainder_division(t_map *map, float weight, int size, char key);
int			ft_check_crossing(t_map *map, int x, int y, size_t check);
int			ft_key_hook(int key, t_map *map);
int			ft_init_textures(t_map *map);
int			ft_control(t_map *map);
void		ft_drawer(t_map *map);
void		ft_solver(t_map *map);
void		ft_error(char *err_str);
void		ft_init_player(t_player *p, t_map *map);
void		ft_casting(t_map *map);
void		*ft_lst_clean(t_list *lst);
t_map		*ft_map_clean(t_map *map);
t_map		*ft_reader(char *av, t_map *map);
t_img		*ft_create_img(t_map *map);
t_img		*ft_img_clean(t_map *map, t_img *img);
t_img		*ft_image_to_pixel(t_img *img, int x, int y, int clr_value);
t_clr		ft_set_color(t_img *img, t_clr clr, t_cst cst, double adjust);

#endif
