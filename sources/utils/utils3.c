/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabarrou <cabarrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:17:17 by cabarrou          #+#    #+#             */
/*   Updated: 2025/10/03 16:11:39 by cabarrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

unsigned long	create_rgb(int r, int g, int b)
{
	return (((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff));
}

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

void	end_file(char *line, int fd)
{
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
}

void	init_keycode(t_mlx_data *data)
{
	int	i;

	i = 0;
	while (i < 7)
	{
		data->keycode[i++] = 0;
	}
}

int	empty(char *line)
{
	if (line[0] == '\n' || line[0] == '\0' || !line[0])
		return (1);
	return (0);
}
