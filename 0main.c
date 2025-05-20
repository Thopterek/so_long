/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndziadzi <ndziadzi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 08:13:00 by ndziadzi          #+#    #+#             */
/*   Updated: 2024/12/19 17:11:55 by ndziadzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// submodule for MLX42:
// git submodule add clone https://github.com/codam-coding-college/MLX42.git
// after clone:
// git submodule update --init --recursive
// make mlx for MLX42 library
// https://git-scm.com/book/en/v2/Git-Tools-Submodules
// Compile MLX42 with DEBUG=1
// WOW SUCH FANCY ___ SUCH CODE ___ SUCHE U_INT32_T | :)

#include "so_long.h"

// static void	leaks(void)
// {
// 	system("leaks so_long");
// }

static int32_t	create_map(char *path)
{
	int		fd;
	int		map_control;
	char	*line;
	char	*last_line;

	last_line = NULL;
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (free(path), ft_printf("Error\nfd fail\n"), 1);
	line = get_next_line(fd);
	while (line != NULL)
	{
		last_line = get_next_line(fd);
		map_control = map_maker(line, last_line);
		if (map_control == 1)
			return (free(path), free(line), free(last_line), close(fd),
				ft_printf("Error\nInvalid map\n"), EXIT_FAILURE);
		free(line);
		if (map_control == 2)
			break ;
		if (last_line != NULL)
			line = last_line;
	}
	return (free(path), close(fd), EXIT_SUCCESS);
}

int32_t	main(int ac, char**av)
{
	char	*path;

	if (ac != 2)
		return (ft_printf("Error\nUsage: ./so_long <map_name>.ber\n"), 1);
	if (ft_strnstr(av[1], ".ber", ft_strlen(av[1])) == NULL)
	{
		ft_printf("Error\nExtension .ber not found\n");
		exit(EXIT_FAILURE);
	}
	path = ft_strjoin("./maps/", av[1]);
	if (path == NULL)
	{
		ft_printf("Error\nProblem with creating path to map\n");
		exit(EXIT_FAILURE);
	}
	if (create_map(path) == 1)
	{
		ft_printf("Error\nWe didn't create a map\n");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
