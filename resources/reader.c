/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrushin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/25 16:19:46 by akrushin          #+#    #+#             */
/*   Updated: 2018/08/25 16:19:48 by akrushin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static t_map	*ft_fill_map(t_map *map)
{
	t_list		*lst;
	char		**str;
	int			x;
	int			y;

	lst = map->lst;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		CLEAN(!(str = ft_strsplit(lst->content, ' ')), map->lst);
		while (x < map->width)
		{
			if ((map->arr[y][x] = ft_atoi(str[x])) < 0 ||
					map->arr[y][x] > map->max_tex)
				return (NULL);
			x++;
		}
		ft_arrdel(str);
		lst = lst->next;
		y++;
	}
	CLEAN(1, map->lst);
	return (map);
}

static void		*ft_create_map(t_map *map, t_list *lst)
{
	int			i;

	map->width = ft_arrcount((char *)lst->content, ' ');
	map->height = ft_lstcount(lst);
	if (!(map->arr = (int **)ft_memalloc(sizeof(int *) * map->width)))
	{
		ft_memdel((void **)&map);
		return (NULL);
	}
	i = 0;
	while (i < map->height)
	{
		if (!(map->arr[i] = (int *)ft_memalloc(sizeof(int) * map->height)))
		{
			while (i > 0)
				ft_memdel((void **)(map->arr + --i));
			ft_memdel((void **)&map);
			return (NULL);
		}
		i++;
	}
	return (NULL);
}

static int		ft_check_valid(t_map *map)
{
	t_set		check;
	int			ret;

	ret = 0;
	check.y = 0;
	check.d = 0;
	check.p = 0;
	while (check.y < map->height)
	{
		check.x = 0;
		while (check.x < map->width)
		{
			if (ft_check_crossing(map, check.x, check.y, 1) == 0)
				check.d++;
			if ((check.x == 0 || check.y == 0 || check.x == map->width - 1 || \
				check.y == map->height - 1) && \
				ft_check_crossing(map, check.x, check.y, 1) == 0)
				check.p++;
			check.x++;
		}
		check.y++;
	}
	check.d ? ret : (ret = 1);
	check.p ? (ret = 1) : ret;
	return (ret);
}

t_map			*ft_reader(char *av, t_map *map)
{
	static int	check = 0;
	t_list		*tmp;
	char		*str;
	int			ret;
	int			fd;

	map->lst = NULL;
	RETURN_NULL((fd = open(av, O_RDONLY)) < 0);
	RETURN_NULL((ret = get_next_line(fd, &str)) == 0);
	ERROR(ret == -1, "\033[31merror: usage folder\033[0m");
	check = ft_arrcount(str, ' ');
	free(str);
	RETURN_NULL((fd = open(av, O_RDONLY)) < 0);
	while ((ret = get_next_line(fd, &str)) > 0)
	{
		RETURN_NULL(check == 0 || ft_arrcount(str, ' ') != (size_t)check || \
			!(tmp = ft_lstnew(str, ft_strlen(str) + sizeof(char))));
		ft_strdel(&str);
		ft_lstadd(&map->lst, tmp);
	}
	ft_create_map(map, ft_lstrev(&map->lst));
	CLEAN(!map, map->lst);
	RETURN_NULL(!ft_fill_map(map) || ft_check_valid(map));
	return (map);
}
