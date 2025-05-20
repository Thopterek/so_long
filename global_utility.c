/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_utility.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndziadzi <ndziadzi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 08:15:44 by ndziadzi          #+#    #+#             */
/*   Updated: 2024/11/26 16:16:41 by ndziadzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// int	random_num(int range)
// {
// 	static int	state = 1;
// 	int			loop_cracker;
// 	int			new;
// 	int			result;
// 	loop_cracker = 0;
// 	result = 0;
// 	new = 0;
// 	if (range <= 0)
// 		return (printf("Error\nDude stop it\n"), -1);
// 	if (state == 0)
// 		state = 1;
// 	while (loop_cracker < range)
// 	{
// 		new = (state ^ (state >> 1)) & 1;
// 		state = (state >> 1) | (new << 3);
// 		result = (result << 1) | new;
// 		loop_cracker++;
// 	}
// 	return (result % range);
// }

char	**actual_copy(char **map, int array_num)
{
	char	**copy;
	int		row;

	row = 0;
	copy = ft_calloc(array_num + 1, sizeof(char *));
	if (copy == NULL)
		return (ft_printf("We failed in creating the copy\n"), NULL);
	row = 0;
	while (row < array_num)
	{
		copy[row] = ft_strdup(map[row]);
		if (copy[row] == NULL)
		{
			while (--row)
				free(copy[row]);
			free(copy);
			return (NULL);
		}
		row++;
	}
	copy[row] = NULL;
	return (copy);
}

void	cleaning(char **map)
{
	int	i;

	i = 0;
	if (map == NULL)
		return ;
	while (map[i] != NULL)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	m_error(void)
{
	ft_printf("Error\n%s\nGraphic part failed\n", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

void	game_ywh(t_game *ga)
{
	ga->y = 0;
	ga->width = 32;
	ga->height = 32;
}
