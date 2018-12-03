/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrushin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 18:19:48 by akrushin          #+#    #+#             */
/*   Updated: 2018/10/23 18:19:49 by akrushin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void		ft_sound(int key)
{
	if (key == NUM_0)
		system("killall afplay 2&>/dev/null >/dev/null");
	else if (key == NUM_1)
	{
		system("killall afplay 2&>/dev/null >/dev/null");
		system("afplay data_files/sounds/song1.mp3&");
	}
	else if (key == NUM_1 + 1)
	{
		system("killall afplay 2&>/dev/null >/dev/null");
		system("afplay data_files/sounds/song2.mp3&");
	}
	else if (key == NUM_1 + 2)
	{
		system("killall afplay 2&>/dev/null >/dev/null");
		system("afplay data_files/sounds/song3.mp3&");
	}
	else if (key == NUM_1 + 3)
	{
		system("killall afplay 2&>/dev/null >/dev/null");
		system("afplay data_files/sounds/song4.mp3&");
	}
}

static void		ft_turn(t_set *set, float angle)
{
	float		x;
	float		d;
	float		c;
	float		s;

	x = set->x;
	d = set->d;
	c = cos(angle);
	s = sin(angle);
	set->x = set->x * c - set->y * s;
	set->y = x * s + set->y * c;
	set->d = set->d * c - set->p * s;
	set->p = d * s + set->p * c;
}

static void		ft_move(t_map *map, float speed)
{
	if (!ft_check_crossing(map, map->player.x + speed * \
		map->player.set.x, map->player.y, 1))
		map->player.x += speed * map->player.set.x;
	if (!ft_check_crossing(map, map->player.x, map->player.y + \
		speed * map->player.set.y, 1))
		map->player.y += speed * map->player.set.y;
}

int				ft_control(t_map *map)
{
	if (map->control.x)
		ft_move(map, SPEED_MOVE);
	if (map->control.y)
		ft_move(map, -1 * SPEED_MOVE);
	if (map->control.d)
		ft_turn(&map->player.set, -1 * SPEED_TURN / ANGLE * M_PI);
	if (map->control.p)
		ft_turn(&map->player.set, SPEED_TURN / ANGLE * M_PI);
	ft_solver(map);
	return (0);
}

int				ft_key_hook(int key, t_map *map)
{
	ft_sound(key);
	if (key == UP)
		map->control.x = !map->control.x;
	if (key == DOWN)
		map->control.y = !map->control.y;
	if (key == LEFT)
		map->control.d = !map->control.d;
	if (key == RIGHT)
		map->control.p = !map->control.p;
	if (key == NUM_ENTER)
		ft_init_player(&map->player, map);
	if (key == ESC || (key == CTRL && key == KEY_C))
	{
		mlx_destroy_window(map->mlx, map->win);
		EXIT_MASSAGE();
		SOUND_OFF();
		system("leaks wolf3d");
		exit(EXIT_SUCCESS);
	}
	ft_solver(map);
	return (0);
}
