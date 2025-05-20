/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2map_utility.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndziadzi <ndziadzi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 12:13:26 by ndziadzi          #+#    #+#             */
/*   Updated: 2024/11/26 16:10:18 by ndziadzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// in struct add an integer for the longest 
// line and always update it here with an if statement :)
// and them call this function in a function that reads 
// the map line by line and save the amount of lines 
// also in the struct id you want to :)
// or however :D	

#include "so_long.h"

static char	*line_characters(char *line, int *exits, int *starts, int *collect)
{
	int			cc;

	cc = 0;
	while (line[cc] != '\n' && line[cc] != '\0')
	{
		if (line[cc] != '0' && line[cc] != '1' && line[cc] != 'C'
			&& line[cc] != 'E' && line[cc] != 'P')
			return (NULL);
		if (line[cc] == 'E')
		{
			*exits += 1;
			if (*exits > 1)
				return (NULL);
		}
		if (line[cc] == 'P')
		{
			*starts += 1;
			if (*starts > 1)
				return (NULL);
		}
		if (line[cc] == 'C')
			*collect += 1;
		cc++;
	}
	return (line);
}

static char	*line_len(char *line)
{
	static int	first;
	static int	cc;
	int			compare;

	compare = 0;
	while (first == 0 && (line[cc] != '\0' && line[cc] != '\n'))
		cc++;
	if (first == 0)
		first += 1;
	while (line[compare] != '\0' && line[compare] != '\n')
		compare++;
	if (compare != cc)
		return (NULL);
	return (line);
}

static char	*line_adding(char *combine, char *line)
{
	char	*tmp;

	if (combine == NULL)
		combine = ft_strdup("");
	if (combine == NULL)
		return (NULL);
	tmp = ft_strjoin(combine, line);
	free(combine);
	if (tmp == NULL)
		return (NULL);
	combine = tmp;
	return (combine);
}

static char	**walls(char **map, int array_num)
{
	static int	cc;
	int			rows;

	rows = 1;
	while (map[0][cc] != '\0')
	{
		if (map[0][cc] != '1')
			return (NULL);
		cc++;
	}
	cc = 0;
	while (rows < array_num - 1)
	{
		if ((map[rows][0] != '1')
			|| (map[rows][ft_strlen(map[rows]) - 1] != '1'))
			return (NULL);
		rows++;
	}
	while (map[rows][cc] != '\0')
	{
		if (map[rows][cc] != '1')
			return (NULL);
		cc++;
	}
	return (map);
}

char	**map_checker(char *line, char *last_line, int array_num, int *collect)
{
	static char	*combine;
	static int	exits;
	static int	starts;
	char		**map;

	if (line_characters(line, &exits, &starts, collect) == NULL)
		return (ft_printf("Error\ninvalid characters\n"), NULL);
	if (line_len(line) == NULL)
		return (ft_printf("Error\nlenght is wrong\n"), NULL);
	combine = line_adding(combine, line);
	if (combine == NULL)
		return (NULL);
	if (last_line == NULL)
	{
		map = ft_split(combine, '\n');
		if (map == NULL)
			return (ft_printf("Error\nThe map in map checker was NULL\n"),
				free(combine), NULL);
		if ((walls(map, array_num) == NULL) || *collect < 1)
			return (ft_printf("Error\n1 or C fail\n"),
				free(combine), cleaning(map), NULL);
		return (free(combine), map);
	}
	return ((char **)line);
}
