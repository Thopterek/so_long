/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5game.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndziadzi <ndziadzi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 08:13:35 by ndziadzi          #+#    #+#             */
/*   Updated: 2024/11/26 15:16:02 by ndziadzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	going_right(t_game *game, int *x, int *y, mlx_image_t *knight)
{
	mlx_delete_image(game->mlx, knight);
	if (game->map_game[*y][*x + 1] == 'C')
	{
		if (damn_changes(game, 1, *x + 1, *y) == 1)
			return (ft_printf("Error\ncollecting failed\n"), 0);
	}
	game->map_game[*y][*x] = '0';
	*x += 1;
	if (game->copy[*y][*x] == 'E')
	{
		if (check_collected(game) == 0)
			mlx_close_window(game->mlx);
	}
	game->map_game[*y][*x] = 'P';
	return (1);
}

static int	going_left(t_game *game, int *x, int *y, mlx_image_t *knight)
{
	mlx_delete_image(game->mlx, knight);
	if (game->map_game[*y][*x - 1] == 'C')
	{
		if (damn_changes(game, 1, *x - 1, *y) == 1)
			return (ft_printf("Error\ncollecting failed\n"), 0);
	}
	game->map_game[*y][*x] = '0';
	*x -= 1;
	if (game->copy[*y][*x] == 'E')
	{
		if (check_collected(game) == 0)
			mlx_close_window(game->mlx);
	}
	game->map_game[*y][*x] = 'P';
	return (1);
}

static int	going_up(t_game *game, int *x, int *y, mlx_image_t *knight)
{
	mlx_delete_image(game->mlx, knight);
	if (game->map_game[*y - 1][*x] == 'C')
	{
		if (damn_changes(game, 1, *x, *y - 1) == 1)
			return (ft_printf("Error\ncollecting failed\n"), 0);
	}
	game->map_game[*y][*x] = '0';
	*y -= 1;
	if (game->copy[*y][*x] == 'E')
	{
		if (check_collected(game) == 0)
			mlx_close_window(game->mlx);
	}
	game->map_game[*y][*x] = 'P';
	return (1);
}

static int	going_down(t_game *game, int *x, int *y, mlx_image_t *knight)
{
	mlx_delete_image(game->mlx, knight);
	if (game->map_game[*y + 1][*x] == 'C')
	{
		if (damn_changes(game, 1, *x, *y + 1) == 1)
			return (ft_printf("Error\ncollecting failed\n"), 0);
	}
	game->map_game[*y][*x] = '0';
	*y += 1;
	if (game->copy[*y][*x] == 'E')
	{
		if (check_collected(game) == 0)
			mlx_close_window(game->mlx);
	}
	game->map_game[*y][*x] = 'P';
	return (1);
}

mlx_texture_t	*move_table(char wasd, t_game *game)
{
	static mlx_texture_t	*player;
	static mlx_image_t		*knight;
	static int				x;
	static int				y;
	int						move;

	move = 0;
	player = init_player(player);
	if ((knight != NULL) && (player != NULL))
	{
		if ((game->map_game[y - 1][x] != '1') && (wasd == 'W'))
			move = going_up(game, &x, &y, knight);
		else if ((game->map_game[y][x - 1] != '1') && (wasd == 'A'))
			move = going_left(game, &x, &y, knight);
		else if ((game->map_game[y][x + 1] != '1') && (wasd == 'D'))
			move = going_right(game, &x, &y, knight);
		else if ((game->map_game[y + 1][x] != '1') && wasd == 'S')
			move = going_down(game, &x, &y, knight);
	}
	if (move == 1 || knight == NULL)
	{
		ft_printf("You moved %d times\n", game->road += 1);
		knight = starting(game, player, &x, &y);
	}
	return (player);
}
