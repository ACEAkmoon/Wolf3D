/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrushin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 18:21:48 by akrushin          #+#    #+#             */
/*   Updated: 2018/10/23 18:21:50 by akrushin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void		ft_draw_mini_map(t_img *img, t_clr clr, t_set set)
{
	t_cst		cst;

	cst.my = set.size * 2 + set.size * set.y;
	while (cst.my < set.size * 2 + (set.size * (set.y + 1)))
	{
		cst.mx = set.size * 2 + set.size * set.x;
		while (cst.mx < set.size * 2 + (set.size * (set.x + 1)))
		{
			ft_image_to_pixel(img, cst.mx, cst.my, \
				ft_set_color(img, clr, cst, 0.5f).value);
			cst.mx++;
		}
		cst.my++;
	}
}

static void		ft_mini_map(t_map *map)
{
	t_set		set;

	set.size = WIN_W / 7 / map->width;
	set.x = LFT_MRGN - 10;
	while (set.x < map->width)
	{
		set.y = TOP_MRGN - 10;
		while (set.y < map->height)
		{
			if (ft_check_crossing(map, set.x, set.y, 1))
				ft_draw_mini_map(map->img, (t_clr)INF_CLR, set);
			set.y++;
		}
		set.x++;
	}
	set.x = map->player.x - 0.5f;
	set.y = map->player.y - 0.5f;
	ft_draw_mini_map(map->img, (t_clr)MINI_MAP_CLR, set);
	set.x += map->player.set.x;
	set.y += map->player.set.y;
	ft_draw_mini_map(map->img, (t_clr)SIGHT_CLR, set);
}

static void		ft_floor_ceiling(t_map *map, int x, int y)
{
	t_cst		cst;
	float		cur;
	float		weight;

	while (y < WIN_H)
	{
		cur = WIN_H / (2.0f * y - WIN_H);
		weight = cur / map->ray.dist;
		cst.mx = ft_remainder_division(map, weight, map->floor->width, 'x');
		cst.my = ft_remainder_division(map, weight, map->floor->height, 'y');
		map->clr.value = FLOOR_CLR;
		ft_image_to_pixel(map->img, x, y, ft_set_color(map->floor, map->clr, \
			cst, 1.0f - cur / VIEW_DIST).value);
		cst.mx = ft_remainder_division(map, weight, map->ceiling->width, 'x');
		cst.my = ft_remainder_division(map, weight, map->ceiling->height, 'y');
		map->clr.value = CEILING_CLR;
		ft_image_to_pixel(map->img, x, WIN_H - y++, ft_set_color(map->ceiling, \
			map->clr, cst, 1.0f - cur / VIEW_DIST).value);
	}
}

static int		ft_column(t_map *map, int x)
{
	t_cst		cst;
	int			y;
	int			end;
	int			start;

	RETURN_NULL(!(map->ray.texture));
	start = (WIN_H - map->ray.height) / 2;
	end = start + map->ray.height;
	start < 0 ? (start = 0) : start;
	end > WIN_H - 1 ? (end = WIN_H - 1) : end;
	y = start;
	while (y < end)
	{
		cst.my = ((y - WIN_H * 0.5f + map->ray.height * 0.5f) *
			map->ray.texture->height) / map->ray.height;
		map->clr.value = WALLS_CLR;
		cst.mx = map->ray.tex_x;
		ft_image_to_pixel(map->img, x, y++, ft_set_color(map->ray.texture, \
			map->clr, cst, map->ray.light).value);
	}
	return (y);
}

void			ft_drawer(t_map *map)
{
	float		cam;
	int			x;
	int			y;

	x = 0;
	while (x < WIN_W)
	{
		cam = 2.0f * x / WIN_W - 1.0f;
		map->ray.set.x = map->player.set.x + map->player.set.d * cam;
		map->ray.set.y = map->player.set.y + map->player.set.p * cam;
		ft_casting(map);
		y = ft_column(map, x);
		ft_floor_ceiling(map, x, y);
		x++;
	}
	ft_mini_map(map);
	mlx_put_image_to_window(map->mlx, map->win, map->img->img, 0, 0);
	mlx_string_put(map->mlx, map->win, LFT_MRGN, WIN_H - TOP_MRGN * 14, \
		INF_CLR, "exit: ESC / reset: ENTER");
	mlx_string_put(map->mlx, map->win, LFT_MRGN, WIN_H - TOP_MRGN * 10, \
		INF_CLR, "move: UP/DOWN/LEFT/RIGHT");
	mlx_string_put(map->mlx, map->win, LFT_MRGN, WIN_H - TOP_MRGN * 6, \
		INF_CLR, "sound: Keypad 1-4/off: 0");
}
