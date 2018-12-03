/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrushin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 21:08:21 by akrushin          #+#    #+#             */
/*   Updated: 2018/11/27 21:08:23 by akrushin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

t_img		*ft_img_clean(t_map *map, t_img *img)
{
	if (img)
	{
		if (img->img)
			mlx_destroy_image(map->mlx, img->img);
		ft_memdel((void **)&img);
	}
	return (NULL);
}

t_map		*ft_map_clean(t_map *map)
{
	if (map)
	{
		if (map->win)
			mlx_destroy_window(map->mlx, map->win);
		if (map->img)
			ft_img_clean(map, map->img);
		ft_memdel((void **)&map);
	}
	return (NULL);
}

void		*ft_lst_clean(t_list *lst)
{
	t_list	*next;
	int		i;

	i = 0;
	while (lst)
	{
		next = lst->next;
		ft_memdel(&lst->content);
		ft_memdel((void **)&lst);
		lst = next;
	}
	return (NULL);
}
