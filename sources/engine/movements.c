/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acolonne <acolonne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 16:30:52 by acolonne          #+#    #+#             */
/*   Updated: 2025/10/06 16:29:12 by acolonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_a_wall(t_mlx_data *data, double x, double y)
{
	if (data->cub_data->map[(int)(y)][(int)(x)] == '1')
		return (0);
	if (data->cub_data->map[(int)(y + 0.1)][(int)(x - 0.1)] == '1')
		return (0);
	if (data->cub_data->map[(int)(y - 0.1)][(int)(x + 0.1)] == '1')
		return (0);
	if (data->cub_data->map[(int)(y - 0.1)][(int)(x - 0.1)] == '1')
		return (0);
	else
		return (1);
}

void	wasd_two(t_mlx_data *data, double speed)
{
	if (data->keycode[d_key])
	{
		if (is_a_wall(data, data->cub_data->player_x + speed
				* -data->cub_data->dir_y, data->cub_data->player_y))
			data->cub_data->player_x += speed * -data->cub_data->dir_y;
		if (is_a_wall(data, data->cub_data->player_x, data->cub_data->player_y
				+ speed * data->cub_data->dir_x))
			data->cub_data->player_y += speed * data->cub_data->dir_x;
	}
	if (data->keycode[a_key])
	{
		if (is_a_wall(data, data->cub_data->player_x + speed
				* data->cub_data->dir_y, data->cub_data->player_y))
			data->cub_data->player_x += speed * data->cub_data->dir_y;
		if (is_a_wall(data, data->cub_data->player_x, data->cub_data->player_y
				+ speed * -data->cub_data->dir_x))
			data->cub_data->player_y += speed * -data->cub_data->dir_x;
	}
}

void	wasd(t_mlx_data *data, double speed)
{
	if (data->keycode[w_key])
	{
		if (is_a_wall(data, data->cub_data->player_x + speed
				* data->cub_data->dir_x, data->cub_data->player_y))
			data->cub_data->player_x += speed * data->cub_data->dir_x;
		if (is_a_wall(data, data->cub_data->player_x, data->cub_data->player_y
				+ speed * data->cub_data->dir_y))
			data->cub_data->player_y += speed * data->cub_data->dir_y;
	}
	if (data->keycode[s_key])
	{
		if (is_a_wall(data, data->cub_data->player_x - speed
				* data->cub_data->dir_x, data->cub_data->player_y))
			data->cub_data->player_x -= speed * data->cub_data->dir_x;
		if (is_a_wall(data, data->cub_data->player_x, data->cub_data->player_y
				- speed * data->cub_data->dir_y))
			data->cub_data->player_y -= speed * data->cub_data->dir_y;
	}
	wasd_two(data, speed);
}

void	rotation(t_mlx_data *data, double olddirx, double oldplanex,
		double rotationspeed)
{
	if (data->keycode[left_arrow])
	{
		data->cub_data->dir_x = data->cub_data->dir_x * cos(-rotationspeed)
			+ (data->cub_data->dir_y * -sin(-rotationspeed));
		data->cub_data->dir_y = olddirx * sin(-rotationspeed)
			+ (data->cub_data->dir_y * cos(-rotationspeed));
		data->cub_data->plane_x = data->cub_data->plane_x * cos(-rotationspeed)
			- data->cub_data->plane_y * sin(-rotationspeed);
		data->cub_data->plane_y = oldplanex * sin(-rotationspeed)
			+ data->cub_data->plane_y * cos(-rotationspeed);
	}
	if (data->keycode[right_arrow])
	{
		data->cub_data->dir_x = data->cub_data->dir_x * cos(rotationspeed)
			+ (data->cub_data->dir_y * -sin(rotationspeed));
		data->cub_data->dir_y = olddirx * sin(rotationspeed)
			+ (data->cub_data->dir_y * cos(rotationspeed));
		data->cub_data->plane_x = data->cub_data->plane_x * cos(rotationspeed)
			- data->cub_data->plane_y * sin(rotationspeed);
		data->cub_data->plane_y = oldplanex * sin(rotationspeed)
			+ data->cub_data->plane_y * cos(rotationspeed);
	}
}

void	player_movements(t_mlx_data *data)
{
	double	speed;
	double	olddirx;
	double	oldplanex;
	double	rotationspeed;

	if (data->keycode[shift])
		speed = 0.02;
	else
		speed = 0.01;
	olddirx = data->cub_data->dir_x;
	oldplanex = data->cub_data->plane_x;
	rotationspeed = 0.03;
	wasd(data, speed);
	rotation(data, olddirx, oldplanex, rotationspeed);
}
