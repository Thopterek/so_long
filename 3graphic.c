/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3graphic.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndziadzi <ndziadzi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 08:13:38 by ndziadzi          #+#    #+#             */
/*   Updated: 2024/12/20 15:55:40 by ndziadzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// EXIT (on the Tiles.png) left 0, top 303, width 50, height 50
// WALL left 0, top 0, width 50, height 50
// FLOOR left 64, top 0, width 50, height 50
// START left 94, top 302, width 50, height 50

#include "so_long.h"

static int	start_and_exit(t_game *game)
{
	mlx_texture_t	*texture;
	mlx_image_t		*start;
	mlx_image_t		*exit;

	game->y = 303;
	game->width = 50;
	game->height = 50;
	texture = mlx_load_png("./textures/space/Tiles.png");
	if (texture == NULL)
		return (ft_printf("Error\nLoad PNG failed\n"), 1);
	start = get_sprite(game, texture, 94);
	exit = get_sprite(game, texture, 0);
	if (start == NULL || exit == NULL)
		return (mlx_delete_texture(texture), ft_printf("Error\nSprite\n"), 1);
	if ((map_render_fifty(game, exit, 'E') == -1)
		|| (map_render_fifty(game, start, 'P') == -1))
		return (mlx_delete_texture(texture), ft_printf("Error\nE or P\n"), 1);
	return (mlx_delete_texture(texture), EXIT_SUCCESS);
}

static int	floor_and_walls(t_game *game)
{
	mlx_texture_t	*texture;
	mlx_image_t		*wall;
	mlx_image_t		*floor;

	game->y = 0;
	game->width = 50;
	game->height = 50;
	texture = mlx_load_png("./textures/space/Tiles.png");
	if (texture == NULL)
		return (ft_printf("Error\nLoad PNG failed\n"), 1);
	wall = get_sprite(game, texture, 0);
	floor = get_sprite(game, texture, 64);
	if (wall == NULL || floor == NULL)
		return (mlx_delete_texture(texture), ft_printf("Error\nSprite\n"), 1);
	if (map_render_fifty(game, wall, '1') == -1)
		return (ft_printf("Error\nWall render failed\n"), 1);
	if ((map_render_fifty(game, floor, '0') == -1)
		|| (map_render_fifty(game, floor, 'C') == -1))
		return (ft_printf("Error\nFloors render failed\n"), 1);
	return (mlx_delete_texture(texture), EXIT_SUCCESS);
}

static void	define_window(char **map, int *width, int *height)
{
	int	hi;
	int	be;

	hi = 0;
	be = 0;
	while (map[hi] != NULL)
		hi++;
	while (map[0][be] != '\0')
		be++;
	*height = 50 * hi;
	*width = 50 * be;
}

static void	key_hook(mlx_key_data_t keydata, void *param)
{
	mlx_texture_t	*player;
	t_game			*game;

	player = NULL;
	game = (t_game *)param;
	if (keydata.key == MLX_KEY_SPACE && keydata.action == MLX_PRESS)
		player = move_and_clean(player, ' ', game);
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
		player = move_and_clean(player, 'W', game);
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
		player = move_and_clean(player, 'A', game);
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
		player = move_and_clean(player, 'D', game);
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
		player = move_and_clean(player, 'S', game);
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		if (player != NULL)
			mlx_delete_texture(player);
		mlx_close_window(game->mlx);
	}
}

int32_t	create_window(char **map)
{
	static int	width;
	static int	height;
	t_game		*game;

	game = malloc(sizeof(t_game));
	game->map_game = map;
	game->road = -1;
	game->copy = actual_copy(game->map_game, check_arrays(game));
	define_window(map, &width, &height);
	game->mlx = mlx_init(width, height, "Sooo loooong", false);
	if (game->mlx == NULL)
		m_error();
	if (floor_and_walls(game) == 1)
		m_error();
	if (start_and_exit(game) == 1)
		m_error();
	if (damn_changes(game, 0, 0, 0) == 1)
		m_error();
	mlx_key_hook(game->mlx, &key_hook, game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
	return (cleaning(game->copy), free(game), EXIT_SUCCESS);
}
