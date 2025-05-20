/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndziadzi <ndziadzi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 08:15:22 by ndziadzi          #+#    #+#             */
/*   Updated: 2024/11/26 16:16:22 by ndziadzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include "MLX42/include/MLX42/MLX42.h"
# include "lib_pri_get/ft_printf.h"
# include "lib_pri_get/libft/libft.h"

typedef struct s_game
{
	char	**map_game;
	char	**copy;
	mlx_t	*mlx;
	int		road;
	int		y;
	int		width;
	int		height;
}			t_game;

typedef struct s_collect
{
	int	collect;
	int	exit;
}	t_collect;

void			m_error(void);
int32_t			create_window(char **map);
int				map_maker(char *line, char *last_line);
char			**map_checker(char *line, char *last_line,
					int array_num, int *collect);
mlx_image_t		*get_sprite(t_game *game, mlx_texture_t *tex, int x);
char			**actual_copy(char **map, int array_num);
int				damn_changes(t_game *game, int cc, int x, int y);
void			cleaning(char **map);
mlx_texture_t	*move_table(char wasd, t_game *game);
mlx_texture_t	*move_and_clean(mlx_texture_t *player, char wasd, t_game *game);
mlx_image_t		*starting(t_game *game, mlx_texture_t *player, int *x, int *y);
mlx_texture_t	*init_player(mlx_texture_t *player);
int32_t			map_render_fifty(t_game *game, mlx_image_t *image, char c);
int				check_collected(t_game *game);
int				check_arrays(t_game *game);
void			game_ywh(t_game *ga);

#endif
