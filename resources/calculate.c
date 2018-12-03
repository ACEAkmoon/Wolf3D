/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrushin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 21:08:21 by akrushin          #+#    #+#             */
/*   Updated: 2018/11/27 21:08:23 by akrushin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int			ft_check_crossing(t_map *map, int x, int y, size_t check)
{
	RETURN_NULL(x < 0 || y < 0 || x > map->width - 1 || y > map->height - 1);
	if (check)
		return (map->arr[y][x]);
	return (1);
}

int			ft_remainder_division(t_map *map, float weight, int size, char key)
{
	int		ret;

	ret = 0;
	if (key == 'x')
		ret = (int)((weight * map->ray.set.d + (1.0f - weight) * \
			map->player.x) * size) % size;
	else if (key == 'y')
		ret = (int)((weight * map->ray.set.p + (1.0f - weight) * \
			map->player.y) * size) % size;
	return (ret);
}

static int	ft_check(t_cst *cst, t_map *map)
{
	int		check;
	int		limit_range;

	check = 0;
	limit_range = 0;
	while (!check && limit_range < VIEW_DIST)
	{
		if (cst->set.x < cst->set.y)
		{
			cst->set.x += cst->set.d;
			cst->mx += cst->stepx;
			map->ray.side = 0;
		}
		else
		{
			cst->set.y += cst->set.p;
			cst->my += cst->stepy;
			map->ray.side = 1;
		}
		if (!ft_check_crossing(map, cst->mx, cst->my, 0))
			break ;
		check = map->arr[cst->my][cst->mx];
		limit_range++;
	}
	return (check);
}

static void	ft_double_casting(t_cst *cst, t_map *map)
{
	int		check;

	if ((check = ft_check(cst, map)))
	{
		map->ray.dist = (map->ray.side ? \
			(cst->my - map->player.y + (1 - cst->stepy) / 2) / map->ray.set.y :
			(cst->mx - map->player.x + (1 - cst->stepx) / 2) / map->ray.set.x);
		map->ray.height = (int)floor(WIN_H / map->ray.dist);
		map->ray.light = 1.0f * (1.0f - map->ray.dist / VIEW_DIST) * \
			(map->ray.side ? 0.9f : 1.f);
		map->ray.texture = map->tex[check];
		cst->wall = (map->ray.side ? map->player.x + map->ray.dist * \
			map->ray.set.x : map->player.y + map->ray.dist * map->ray.set.y);
		cst->wall -= floor(cst->wall);
		map->ray.tex_x = (int)(cst->wall * map->ray.texture->width);
		map->ray.set.d = (float)cst->mx + (map->ray.side ? cst->wall : 0) + \
			(!map->ray.side && map->ray.set.x < 0 ? 1.0f : 0);
		map->ray.set.p = (float)cst->my + (map->ray.side ? 0 : cst->wall) + \
			(map->ray.side && map->ray.set.y < 0 ? 1.0f : 0);
	}
}

void		ft_casting(t_map *map)
{
	t_cst	cst;

	cst.mx = (int)map->player.x;
	cst.my = (int)map->player.y;
	cst.set.d = sqrt((map->ray.set.y * map->ray.set.y) / \
		(map->ray.set.x * map->ray.set.x) + 1);
	cst.set.p = sqrt((map->ray.set.x * map->ray.set.x) / \
		(map->ray.set.y * map->ray.set.y) + 1);
	cst.stepx = (map->ray.set.x < 0 ? -1 : 1);
	cst.stepy = (map->ray.set.y < 0 ? -1 : 1);
	cst.set.x = (map->ray.set.x < 0 ? map->player.x - cst.mx : \
		cst.mx - map->player.x + 1) * cst.set.d;
	cst.set.y = (map->ray.set.y < 0 ? map->player.y - cst.my : \
		cst.my - map->player.y + 1) * cst.set.p;
	map->ray.height = 0;
	ft_double_casting(&cst, map);
}
