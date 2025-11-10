/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acolonne <acolonne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 14:53:41 by acolonne          #+#    #+#             */
/*   Updated: 2025/10/06 17:27:11 by acolonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	black(t_mlx_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i <= 800)
	{
		while (j <= 1280)
		{
			my_mlx_pixel_put(data, i, j, 0);
			j++;
		}
		j = 0;
		i++;
	}
}

/* double	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000.0 + tv.tv_usec / 1000.0);
} */

/*
// data->old_time = data->current_time;
// data->current_time = get_time();
// data->frame_time = (data->current_time - data->old_time) / 1000.0;
*/

int	draw_player_square(t_mlx_data *data, int x, int y, int color)
{
	int	i;
	int	goal_a;
	int	j;
	int	goal_b;

	if (data->win_ptr == NULL)
		return (1);
	i = x;
	j = y;
	goal_a = i + 2;
	goal_b = j + 2;
	while (i < goal_a)
	{
		while (j < goal_b)
		{
			my_mlx_pixel_put(data, i, j, color);
			j++;
		}
		j = y;
		i++;
	}
	return (0);
}

void	draw_map_black(t_mlx_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < 128)
	{
		j = 0;
		while (j < 128)
		{
			my_mlx_pixel_put(data, j, i, 0);
			j++;
		}
		i++;
	}
}

int	refresh(t_mlx_data *data)
{
	player_movements(data);
	black(data);
	raycast_start(data);
	draw_map_black(data);
	draw_map(data);
	draw_player_square(data, 64, 64, 500);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->big_img, 0, 0);
	return (0);
}
