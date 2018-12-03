/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrushin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 18:19:07 by akrushin          #+#    #+#             */
/*   Updated: 2018/10/23 18:19:09 by akrushin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

t_img			*ft_image_to_pixel(t_img *img, int x, int y, int clr_value)
{
	if (!(x < 0 || y < 0 || x >= img->width || y >= img->height))
		*(int *)(img->ptr + ((x + y * img->width) * img->bt_px)) = clr_value;
	return (img);
}

void			ft_init_player(t_player *p, t_map *map)
{
	int			x;
	int			y;
	int			f;

	y = 0;
	f = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (!(f = ft_check_crossing(map, x, y, 1)))
				break ;
			x++;
		}
		if (!f)
			break ;
		y++;
	}
	p->x = x + 0.5f;
	p->y = y + 0.5f;
	p->set.x = 1.0f;
	p->set.y = 0.0f;
	p->set.d = 0.0f;
	p->set.p = 2.0f / 3.0f;
}

t_img			*ft_create_img(t_map *map)
{
	t_img		*img;

	RETURN_NULL(!(img = ft_memalloc(sizeof(t_img))));
	if (!(img->img = mlx_new_image(map->mlx, WIN_W, WIN_H)))
		return (ft_img_clean(map, img));
	img->ptr = mlx_get_data_addr(img->img, &img->bt_px, &img->size_line,
		&img->endian);
	img->bt_px /= 8;
	img->width = WIN_W;
	img->height = WIN_H;
	return (img);
}

static t_img	*ft_path_to_img(char *path_tiles, t_map *map)
{
	t_img		*img;
	int			i;

	RETURN_NULL(!(img = ft_memalloc(sizeof(t_img))));
	if (!(img->img = mlx_xpm_file_to_image(map->mlx, path_tiles, \
		&img->width, &img->height)))
		return (ft_img_clean(map, img));
	img->ptr = mlx_get_data_addr(img->img, &img->bt_px, &img->size_line,
		&img->endian);
	img->bt_px /= 8;
	img->width = img->size_line / img->bt_px;
	img->height = img->size_line / img->bt_px;
	if (!img)
	{
		i = 0;
		ft_strdel(&path_tiles);
		while (i < TEX_SIZE)
			ft_img_clean(map, map->tex[i++]);
	}
	return (img);
}

int				ft_init_textures(t_map *map)
{
	static char	*tiles[TEX_SIZE] = { "brick.xpm", "wood.xpm",
		"flag.xpm", "stone.xpm", "forest.xpm", "brick_red.xpm",
		"eagle.xpm", "portrait.xpm", NULL };
	char		*path_tiles;
	t_img		*img;
	int			i;

	i = 1;
	while (i < TEX_SIZE && tiles[i - 1])
	{
		path_tiles = ft_strjoin((SRC_TILES), tiles[i - 1]);
		if (!(img = ft_path_to_img(path_tiles, map)))
			return (1);
		ft_strdel(&path_tiles);
		map->tex[i++] = img;
	}
	map->max_tex = i - 1;
	map->tex[0] = NULL;
	map->floor = map->tex[2];
	map->ceiling = map->tex[4];
	return (0);
}
