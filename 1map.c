/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1map.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndziadzi <ndziadzi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 08:13:42 by ndziadzi          #+#    #+#             */
/*   Updated: 2024/11/26 16:08:59 by ndziadzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	actual_flood_fill(char **copy, int x, int y, t_collect *fe)
{
	if (copy[y][x] == '1' || copy[y][x] == 'V')
		return ;
	if (copy[y][x] == 'C')
		fe->collect += 1;
	if (copy[y][x] == 'E')
		fe->exit += 1;
	copy[y][x] = 'V';
	actual_flood_fill(copy, x + 1, y, fe);
	actual_flood_fill(copy, x - 1, y, fe);
	actual_flood_fill(copy, x, y + 1, fe);
	actual_flood_fill(copy, x, y - 1, fe);
}

static int	iam_in_your_walls(char **map, int pl_x, int p_yy, int *collect)
{
	t_collect	*fe;

	fe = malloc(sizeof(t_collect));
	fe->collect = 0;
	fe->exit = 0;
	actual_flood_fill(map, pl_x, p_yy, fe);
	if (fe->collect == *collect && fe->exit > 0)
		return (free(fe), EXIT_SUCCESS);
	return (ft_printf("Error\nfound %d out of %d\n", fe->collect, *collect),
		ft_printf("If its the same then no exit\n"), free(fe), EXIT_FAILURE);
}

static int	find_x_and_y(char **map, int *pl_x, int *p_yy, int array_num)
{
	int	height;
	int	belly;

	height = 0;
	belly = 0;
	while (height < array_num)
	{
		while (map[height][belly] != '\0')
		{
			if (map[height][belly] == 'P')
				return (*pl_x = belly, *p_yy = height, EXIT_SUCCESS);
			belly++;
		}
		belly = 0;
		height++;
	}
	return (ft_printf("Error\nWe didn't find the start\n"), EXIT_FAILURE);
}

static int	flood_fill(char **map, int array_num, int *collect)
{
	int	pl_x;
	int	p_yy;

	if (find_x_and_y(map, &pl_x, &p_yy, array_num) == 1)
		return (EXIT_FAILURE);
	if (iam_in_your_walls(map, pl_x, p_yy, collect) == 1)
		return (ft_printf("Error\nYou can't reach everything\n"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	map_maker(char *line, char *last_line)
{
	static int		array_num;
	static char		**map;
	static int		collect;
	char			**copy;

	array_num += 1;
	copy = NULL;
	map = map_checker(line, last_line, array_num, &collect);
	if (map == NULL)
		return (ft_printf("Error\nMap check fail\n"), EXIT_FAILURE);
	if (last_line == NULL)
	{
		copy = actual_copy(map, array_num);
		if (flood_fill(copy, array_num, &collect) == 1)
			return (cleaning(copy), ft_printf("Error\nFlood fill failed\n"), 1);
		cleaning(copy);
		if (create_window(map) == 1)
			return (ft_printf("Error\nWe didn't create a window\n"), 1);
		return (2);
	}
	return (EXIT_SUCCESS);
}
