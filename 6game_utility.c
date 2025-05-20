/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6game_utility.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndziadzi <ndziadzi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:25:50 by ndziadzi          #+#    #+#             */
/*   Updated: 2024/11/26 16:18:22 by ndziadzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

mlx_image_t	*starting(t_game *game, mlx_texture_t *player, int *x, int *y)
{
	mlx_image_t	*knight;
	int			hi;
	int			be;

	hi = 0;
	be = 0;
	game_ywh(game);
	knight = get_sprite(game, player, 0);
	if (knight == NULL)
		return (mlx_delete_texture(player),
			ft_printf("Error\nStar failed"), NULL);
	while (game->map_game[hi] != NULL)
	{
		while (game->map_game[hi][be] != '\0')
		{
			if (game->map_game[hi][be] == 'P')
				return (*x = be, *y = hi,
					mlx_image_to_window(game->mlx, knight, *x * 50, *y * 50),
					knight);
			be += 1;
		}
		be = 0;
		hi += 1;
	}
	return (knight);
}

mlx_texture_t	*init_player(mlx_texture_t *player)
{
	if (player == NULL)
	{
		player = mlx_load_png("./textures/sprites/player/kn/id/is.png");
		if (player == NULL)
			return (NULL);
	}
	return (player);
}

int	check_collected(t_game *game)
{
	int	h;
	int	w;

	h = 0;
	w = 0;
	while (game->map_game[h] != NULL)
	{
		while (game->map_game[h][w] != '\0')
		{
			if (game->map_game[h][w] == 'C')
				return (1);
			w++;
		}
		w = 0;
		h++;
	}
	return (0);
}

int	check_arrays(t_game *game)
{
	int	h;
	int	w;

	h = 0;
	w = 0;
	while (game->map_game[h] != NULL)
		h++;
	return (h);
}

mlx_texture_t	*move_and_clean(mlx_texture_t *player, char wasd, t_game *game)
{
	if (player != NULL)
		mlx_delete_texture(player);
	player = move_table(wasd, game);
	return (player);
}
