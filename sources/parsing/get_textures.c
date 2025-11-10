/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acolonne <acolonne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 16:59:24 by acolonne          #+#    #+#             */
/*   Updated: 2025/10/28 14:23:52 by acolonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	*cpy_texture(char *line)
{
	int		i;
	int		j;
	char	*texture;

	i = 0;
	j = 0;
	while (line && line[i] && line[i] != 32)
		i++;
	while (line && line[i] && (line[i] == 32 || line[i] == '\t'))
		i++;
	texture = malloc(ft_strlen(&line[i]));
	if (!texture)
		return (0);
	while (line && line[i] && line[i] != '\n'
		&& line[i] != 32 && line[i] != '\t')
	{
		texture[j] = line[i];
		i++;
		j++;
	}
	texture[j] = '\0';
	return (texture);
}

int	skip_spaces(char *line, int i)
{
	int	j;

	j = i;
	while (line && line[i] && (line[i] == 32 || line[i] == '\t')
		&& line[i] != '\n')
		i++;
	while (line && line[i] && (line[i] > 47 && line[i] < 58))
		i++;
	if (line && line[i] && (line[i] < 48 || line[i] > 57))
		i++;
	while (line && line[i] && (line[i] == 32 || line[i] == '\t')
		&& line[i] != '\n')
		i++;
	return (i - j);
}

long	cpy_colors(char *line)
{
	int	i;
	int	r;
	int	g;
	int	b;

	i = 0;
	r = -1;
	g = -1;
	b = -1;
	i += skip_spaces(line, i);
	r = ft_atoi(&line[i]);
	i += skip_spaces(line, i);
	g = ft_atoi(&line[i]);
	i += skip_spaces(line, i);
	b = ft_atoi(&line[i]);
	i += skip_spaces(line, i);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (-2);
	return (create_rgb(r, g, b));
}

int	check_texture(char *line, t_data *data)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == 32 || line[i] == '\t'))
		i++;
	if (!ft_strncmp(&line[i], "NO", 2) && !data->no)
		data->no = cpy_texture(&line[i]);
	else if (!ft_strncmp(&line[i], "SO", 2) && !data->so)
		data->so = cpy_texture(&line[i]);
	else if (!ft_strncmp(&line[i], "WE", 2) && !data->we)
		data->we = cpy_texture(&line[i]);
	else if (!ft_strncmp(&line[i], "EA", 2) && !data->ea)
		data->ea = cpy_texture(&line[i]);
	else if (!ft_strncmp(&line[i], "F", 1) && data->f == -1)
		data->f = cpy_colors(&line[i]);
	else if (!ft_strncmp(&line[i], "C", 1) && data->c == -1)
		data->c = cpy_colors(&line[i]);
	else if (check_empty(line))
		return (0);
	else if (start_map(line))
		return (2);
	else
		return (1);
	return (0);
}

int	get_textures(int fd, t_data *data)
{
	char	*line;
	int		code;

	code = 0;
	line = get_next_line(fd);
	while (line)
	{
		code = check_texture(line, data);
		if (code == 2)
			break ;
		if (code == 1)
		{
			end_file(line, fd);
			return (1);
		}
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	line = get_next_line(fd);
	end_file(line, fd);
	return (0);
}
