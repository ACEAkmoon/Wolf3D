/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrushin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 18:20:44 by akrushin          #+#    #+#             */
/*   Updated: 2018/10/23 18:20:45 by akrushin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void			ft_error(char *err_str)
{
	*err_str ? ft_putendl(err_str) : ft_putendl("\033[31merror\033[0m");
	EXIT_MASSAGE();
	SOUND_OFF();
	exit(EXIT_FAILURE);
}

static void		ft_display_controls(void)
{
	ft_putstr("\033[94;1m\
_______________________________\n\
CONTROLS:\n\
\033[32;1mTranslation:\033[0m\n\
	MOVE: Key: UP, DOWN\n\
	TURN: Key: LEFT, RIGHT\n\
\n\
\033[32;1mSounds:\033[0m\n\
	PLAY: Keypad: 1-4\n\
	OFF:  Keypad: 0\n\
\n\
\033[32;1mReset:\033[0m\n\
	Keypad: ENTER\n\
\n\
\033[32;1mExit:\033[0m\n\
	IN: Key: Esc\n\
\033[94;1m_______________________________\n\
\033[0m");
}

static int		exit_x(void)
{
	EXIT_MASSAGE();
	SOUND_OFF();
	exit(EXIT_SUCCESS);
}

int				main(int ac, char **av)
{
	t_map		*map;

	if (ac == 2)
	{
		RETURN_NULL(!(map = ft_memalloc(sizeof(t_map))));
		MAP_DELL(!(map->mlx = mlx_init()), map);
		MAP_DELL(!(map->win = \
			mlx_new_window(map->mlx, WIN_W, WIN_H, NAME)), map);
		MAP_DELL(!(map->img = ft_create_img(map)), map);
		ERROR(ft_init_textures(map), "\033[31merror: initial texture\033[0m");
		ERROR(!(map = ft_reader(av[1], map)), "\033[31merror: read map\033[0m");
		ft_display_controls();
		ft_init_player(&map->player, map);
		ft_solver(map);
		system("afplay data_files/sounds/intro.mp3&");
		mlx_do_key_autorepeatoff(map->mlx);
		mlx_key_hook(map->win, ft_key_hook, map);
		mlx_hook(map->win, 2, 1L << 0, ft_key_hook, map);
		mlx_hook(map->win, 17, 1L << 17, exit_x, map);
		mlx_loop_hook(map->mlx, ft_control, map);
		mlx_loop(map->mlx);
		return (exit_x());
	}
	ft_error("\033[33musage: ./wolf3d [mapfile]\033[0m");
	return (EXIT_FAILURE);
}
