/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acolonne <acolonne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 17:21:32 by acolonne          #+#    #+#             */
/*   Updated: 2025/10/20 16:36:57 by acolonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	count_lines(int fd)
{
	int		i;
	char	*line;

	i = 0;
	line = get_next_line(fd);
	while (line && start_map(line) == 0)
	{
		free(line);
		line = get_next_line(fd);
	}
	while (line && empty(line) == 0)
	{
		free(line);
		line = get_next_line(fd);
		i++;
	}
	i = check_line(fd, line, i);
	return (i);
}

char	*ft_strdup(char *line)
{
	char	*str;
	int		i;

	i = 0;
	str = 0;
	str = malloc(ft_strlen(line) + 1);
	if (!str)
		return (0);
	while (line && line[i] && line[i] != '\n')
	{
		str[i] = line[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

void	free_split_error(char **split, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		free(split[j]);
		j++;
	}
	free(split);
}

int	copy_map(t_data *data, int fd, int nb_line, int i)
{
	char	*line;

	data->map = malloc(sizeof(char **) * (nb_line + 1));
	if (!data->map)
		return (1);
	line = get_next_line(fd);
	while (line && start_map(line) == 0)
	{
		free(line);
		line = get_next_line(fd);
	}
	while (line)
	{
		data->map[i] = ft_strdup(line);
		if (!data->map[i])
			return (1);
		free(line);
		line = get_next_line(fd);
		i++;
	}
	data->map[i] = NULL;
	return (0);
}

/* J'ai enleve le free_split_error(data->map, i); >> redondant */

int	get_map(t_data *data, int fd, char *file)
{
	int	nb_line;
	int	i;

	i = 0;
	nb_line = count_lines(fd);
	if (nb_line == -1)
		return (1);
	close(fd);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (1);
	if (copy_map(data, fd, nb_line, i))
		return (1);
	i = 0;
	close(fd);
	return (0);
}
