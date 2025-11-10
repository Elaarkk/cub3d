/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acolonne <acolonne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 14:56:05 by cabarrou          #+#    #+#             */
/*   Updated: 2025/10/28 14:25:47 by acolonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_filename(char *file, char *filename)
{
	int	len;
	int	i;

	i = 0;
	(void)filename;
	(void)len;
	while ((file[i] == 32 || file[i] == '\t') && file[i])
		i++;
	while (file[i] && file[i] != 32 && file[i] != '\t')
		i++;
	i -= 4;
	if (ft_strncmp(&file[i], filename, 4) == 0)
		return (0);
	return (1);
}

int	check_open(t_data *data)
{
	int	fd_n;
	int	fd_s;
	int	fd_w;
	int	fd_e;

	fd_n = open(data->no, O_RDONLY);
	if (fd_n == -1)
		return (1);
	close(fd_n);
	fd_s = open(data->so, O_RDONLY);
	if (fd_s == -1)
		return (1);
	close(fd_s);
	fd_w = open(data->we, O_RDONLY);
	if (fd_w == -1)
		return (1);
	close(fd_w);
	fd_e = open(data->ea, O_RDONLY);
	if (fd_e == -1)
		return (1);
	close(fd_e);
	return (0);
}

int	check_xpm(t_data *data)
{
	if (check_filename(data->no, ".xpm"))
		return (1);
	if (check_filename(data->so, ".xpm"))
		return (1);
	if (check_filename(data->we, ".xpm"))
		return (1);
	if (check_filename(data->ea, ".xpm"))
		return (1);
	if (check_open(data))
		return (1);
	return (0);
}

int	verify_texture(t_data *data)
{
	if (!data->so || !data->no || !data->ea || !data->we)
	{
		print_error("Missing texture\n");
		return (1);
	}
	if (data->f == -1 || data->c == -1)
	{
		print_error("Missing colors\n");
		return (1);
	}
	if (data->f < 0 || data->c < 0)
	{
		print_error("Invalid colors\n");
		return (1);
	}
	if (check_xpm(data))
	{
		print_error("Wrong texture file\n");
		return (1);
	}
	return (0);
}
