/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrushin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 21:15:32 by akrushin          #+#    #+#             */
/*   Updated: 2018/11/06 21:15:36 by akrushin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void		*ft_thread(void *in)
{
	t_thread	*t;
	int			x;
	int			y;

	t = (t_thread *)in;
	y = (WIN_H / THREADS) * t->id;
	while (y < WIN_H / THREADS * (t->id + 1))
	{
		x = 0;
		while (x < WIN_W)
		{
			*(t->map->img) = \
				*(ft_image_to_pixel(t->map->img, x, y, t->map->clr.value));
			x++;
		}
		y++;
	}
	return (NULL);
}

void			ft_solver(t_map *map)
{
	int			i;

	i = 0;
	while (i < THREADS)
	{
		map->threads[i].id = i;
		map->threads[i].map = map;
		pthread_create(map->pthread + i, NULL, ft_thread, &(map->threads[i]));
		i++;
	}
	i = 0;
	while (i < THREADS)
		pthread_join(map->pthread[i++], NULL);
	ft_drawer(map);
}
