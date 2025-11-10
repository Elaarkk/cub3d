/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acolonne <acolonne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 18:20:16 by acolonne          #+#    #+#             */
/*   Updated: 2025/10/06 17:28:47 by acolonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	draw_tile(t_mlx_data *data, double x, double y, int color)
{
	double	i;
	double	goal_a;
	double	j;
	double	goal_b;

	if (data->win_ptr == NULL)
		return (1);
	i = x;
	j = y;
	goal_a = i + data->tile_size;
	goal_b = j + data->tile_size;
	while (i < goal_a && i < 128)
	{
		while (j < goal_b && j < 128)
		{
			my_mlx_pixel_put(data, i, j, color);
			j++;
		}
		j = y;
		i++;
	}
	return (0);
}

void	draw_tiles_map(t_mlx_data *data, double i, double j, t_minimap *minimap)
{
	if (data->cub_data->map[(int)i][(int)j] == '1')
		draw_tile(data, minimap->x, minimap->y, 0x2c542c);
	else if (data->cub_data->map[(int)i][(int)j] == '0'
					|| data->cub_data->map[(int)i][(int)j] == 'E'
					|| data->cub_data->map[(int)i][(int)j] == 'N'
					|| data->cub_data->map[(int)i][(int)j] == 'W'
					|| data->cub_data->map[(int)i][(int)j] == 'S')
		draw_tile(data, minimap->x, minimap->y, 0xc2bfb0);
	else
		draw_tile(data, minimap->x, minimap->y, 0);
}

void	trace_line_map(t_mlx_data *data, double i, double j, t_minimap *minimap)
{
	while (j <= 0)
	{
		j++;
		minimap->x += data->tile_size;
	}
	while ((int)j < (int)ft_strlen(data->cub_data->map[(int)i]))
	{
		draw_tiles_map(data, i, j, minimap);
		j++;
		minimap->x += data->tile_size;
	}
}

void	draw_map(t_mlx_data *data)
{
	double		i;
	double		j;
	t_minimap	minimap;

	j = 0;
	minimap.offset_x = ((data->cub_data->player_x - 0.5)
			- (int)data->cub_data->player_x) * data->tile_size;
	minimap.offset_y = ((data->cub_data->player_y - 0.5)
			- (int)data->cub_data->player_y) * data->tile_size;
	i = data->cub_data->player_y - 6;
	minimap.y = 0 - minimap.offset_y;
	while (i <= 0)
	{
		minimap.y += data->tile_size;
		i++;
	}
	while (data->cub_data->map[(int)i])
	{
		j = data->cub_data->player_x - 6;
		minimap.x = 0 - minimap.offset_x;
		trace_line_map(data, i, j, &minimap);
		minimap.y += data->tile_size;
		i++;
	}
}

void	draw_player(t_mlx_data *data)
{
	int	x;
	int	y;

	x = data->cub_data->player_x;
	y = data->cub_data->player_y;
	x *= data->tile_size;
	y *= data->tile_size;
	x += data->tile_size / 2;
	y += data->tile_size / 2;
	draw_player_square(data, x, y, 500);
}
