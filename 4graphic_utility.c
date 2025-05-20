/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4graphic_utility.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndziadzi <ndziadzi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 12:07:21 by ndziadzi          #+#    #+#             */
/*   Updated: 2024/11/26 16:17:06 by ndziadzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// C death 1 to 2 (left 32/128), top 32, width 32, height 32
// C death 3, left 224, top 24, width 32, height 40
// C death 4, left 320, top 15, width 32, height 49
// C death 5, left 416, top 24, width 32, height 40
// C death 6 to 8 (left 512/608/704), top 32, width 32, height 32
// mlx_texture_t	*death;
// if (I CLICK ON THIS)
// {
// 	death = mlx_load_png("./textures/sprites/collect/Death/Death-Sheet.png");
// 	if (death == NULL)
// 		return (1);
// }
// COLLECTIBLE IDLE 1 to 4 (left 0/32/64/96), width 32, height 32
// animation[1] = get_sprite(mlx, idle, 32, 0, 32, 32);
// animation[2] = get_sprite(mlx, idle, 64, 0, 32, 32);
// animation[3] = get_sprite(mlx, idle, 96, 0, 32, 32);

mlx_image_t	*get_sprite(t_game *game, mlx_texture_t *tex, int x)
{
	int			hi;
	int			be;
	uint8_t		*sour;
	uint8_t		*dest;
	mlx_image_t	*sprite;

	hi = 0;
	be = 0;
	sprite = mlx_new_image(game->mlx, game->width, game->height);
	if (sprite == NULL)
		return (ft_printf("Error\nCouldn't grab a sprite\n"), NULL);
	while (hi < game->height)
	{
		while (be < game->width)
		{
			sour = &tex->pixels[((game->y + hi) * tex->width + (be + x)) * 4];
			dest = &sprite->pixels[(hi * game->width + be) * 4];
			ft_memcpy(dest, sour, 4);
			be++;
		}
		be = 0;
		hi++;
	}
	return (sprite);
}

static mlx_image_t	**allocate_skeletons(t_game *game, mlx_image_t **skeletons)
{
	int	cc;
	int	high;
	int	belly;
	int	count;

	cc = 0;
	high = 0;
	belly = 0;
	count = 0;
	while (game->map_game[high] != NULL)
	{
		while (game->map_game[high][belly] != '\0')
		{
			if (game->map_game[high][belly] == 'C')
				count++;
			belly++;
		}
		belly = 0;
		high++;
	}
	skeletons = ft_calloc(count, sizeof(mlx_image_t *));
	if (skeletons == NULL)
		return (NULL);
	return (skeletons);
}

static mlx_image_t	**loop_logic(t_game *ga, int hi, mlx_image_t **ske, int *cc)
{
	mlx_texture_t		*collect;
	int					belly;

	belly = 0;
	game_ywh(ga);
	collect = mlx_load_png("./textures/sprites/cl/Idle/is.png");
	if (collect == NULL)
		return (NULL);
	ske = allocate_skeletons(ga, ske);
	while ((ske != NULL) && (ga->map_game[hi] != NULL))
	{
		while (ga->map_game[hi][belly] != '\0')
		{
			if (ga->map_game[hi][belly] == 'C')
			{
				ske[*cc] = get_sprite(ga, collect, 0);
				mlx_image_to_window(ga->mlx, ske[*cc], belly * 50, hi * 50);
				*cc += 1;
			}
			belly++;
		}
		belly = 0;
		hi++;
	}
	return (mlx_delete_texture(collect), ske);
}

int	damn_changes(t_game *game, int cc, int x, int y)
{
	static mlx_image_t	**skeletons;
	static int			count;
	int					high;

	high = 0;
	if (cc == 0)
	{
		skeletons = loop_logic(game, high, skeletons, &count);
		if (skeletons == NULL)
			return (EXIT_FAILURE);
	}
	if (skeletons != NULL && cc == 1)
	{
		while (high < count)
		{
			if (skeletons[high] != NULL
				&& skeletons[high]->instances[0].x == x * 50
				&& skeletons[high]->instances[0].y == y * 50)
				return (mlx_delete_image(game->mlx, skeletons[high]),
					skeletons[high] = NULL, EXIT_SUCCESS);
			high++;
		}
	}
	return (EXIT_SUCCESS);
}

int32_t	map_render_fifty(t_game *g, mlx_image_t *i, char c)
{
	int	hi;
	int	be;

	hi = 0;
	be = 0;
	while (g->map_game[hi] != NULL)
	{
		while (g->map_game[hi][be] != '\0')
		{
			if (g->map_game[hi][be] == c)
				if (mlx_image_to_window(g->mlx, i, be * 50, hi * 50) == -1)
					return (EXIT_FAILURE);
			be++;
		}
		be = 0;
		hi++;
	}
	return (EXIT_SUCCESS);
}
