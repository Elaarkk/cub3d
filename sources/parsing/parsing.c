/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acolonne <acolonne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 19:09:17 by cabarrou          #+#    #+#             */
/*   Updated: 2025/11/10 16:28:46 by acolonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_dir(char **map, int i, int j)
{
	if (i == 0 || j == 0)
		return (1);
	if (!map[i - 1])
		return (1);
	else if (!map[i + 1][j])
		return (1);
	else if (!map[i][j - 1])
		return (1);
	else if (!map[i + 1])
		return (1);
	else if (!map[i][j + 1])
		return (1);
	else if (map[i - 1][j] == ' ')
		return (1);
	else if (map[i][j - 1] == ' ')
		return (1);
	else if (map[i + 1][j] == ' ')
		return (1);
	else if (map[i][j + 1] == ' ')
		return (1);
	else
		return (0);
}

int	check_walls(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] != '1' && data->map[i][j] != ' ')
			{
				if (check_dir(data->map, i, j))
				{
					print_error("Map not surrounded by walls\n");
					return (1);
				}
			}
			j++;
		}
		i++;
	}
	return (0);
}

void	replace_spaces(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == ' ')
				map[i][j] = '1';
			j++;
		}
		i++;
	}
}

int	get_map_info(int fd, t_data *data, char *file)
{
	if (get_textures(fd, data))
	{
		print_error("Texture error\n");
		return (1);
	}
	if (verify_texture(data))
		return (1);
	close(fd);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (1);
	if (get_map(data, fd, file))
	{
		print_error("Map error\n");
		return (1);
	}
	if (check_walls(data))
		return (1);
	replace_spaces(data->map);
	if (verify_map(data))
		return (1);
	return (0);
}

int	parsing(char *file, t_data *data)
{
	int	fd;

	if (check_filename(file, ".cub"))
	{
		print_error("Wrong file name\n");
		return (1);
	}
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		print_error("No such file\n");
		return (1);
	}
	if (get_map_info(fd, data, file))
	{
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}
