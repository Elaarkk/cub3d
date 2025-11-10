/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_maths.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabarrou <cabarrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 18:22:17 by acolonne          #+#    #+#             */
/*   Updated: 2025/10/03 13:42:47 by cabarrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	deltadist_calc(t_maths *maths)
{
	if (maths->raydir_x < 0)
	{
		maths->step_x = -1;
		maths->sidedist_x = (maths->pos_x - maths->map_x) * maths->deltadist_x;
	}
	else
	{
		maths->step_x = 1;
		maths->sidedist_x = (maths->map_x + 1.0 - maths->pos_x)
			* maths->deltadist_x;
	}
	if (maths->raydir_y < 0)
	{
		maths->step_y = -1;
		maths->sidedist_y = (maths->pos_y - maths->map_y) * maths->deltadist_y;
	}
	else
	{
		maths->step_y = 1;
		maths->sidedist_y = (maths->map_y + 1.0 - maths->pos_y)
			* maths->deltadist_y;
	}
}

void	hit_loop(t_mlx_data *data, t_maths *maths, int hit)
{
	while (hit == 0)
	{
		if (maths->sidedist_x < maths->sidedist_y)
		{
			maths->sidedist_x += maths->deltadist_x;
			maths->map_x += maths->step_x;
			maths->side = 0;
		}
		else
		{
			maths->sidedist_y += maths->deltadist_y;
			maths->map_y += maths->step_y;
			maths->side = 1;
		}
		if (data->cub_data->map[maths->map_y][maths->map_x] == '1')
			hit = 1;
	}
}

void	ray_loop(t_mlx_data *data, t_maths *maths, int x, int hit)
{
	hit = 0;
	maths->camera_x = 2 * x / (double)data->x - 1;
	maths->raydir_x = maths->dir_x + maths->plane_x * maths->camera_x;
	maths->raydir_y = maths->dir_y + maths->plane_y * maths->camera_x;
	maths->map_x = (int)maths->pos_x;
	maths->map_y = (int)maths->pos_y;
	if (maths->raydir_x == 0)
		maths->deltadist_x = 1e30;
	else
		maths->deltadist_x = fabs(1 / maths->raydir_x);
	if (maths->raydir_y == 0)
		maths->deltadist_y = 1e30;
	else
		maths->deltadist_y = fabs(1 / maths->raydir_y);
	deltadist_calc(maths);
	hit_loop(data, maths, hit);
	if (maths->side == 0)
		maths->perpwalldist = (maths->sidedist_x - maths->deltadist_x);
	else
		maths->perpwalldist = (maths->sidedist_y - maths->deltadist_y);
	maths->hit_x = maths->pos_x + maths->raydir_x * maths->perpwalldist;
	maths->hit_y = maths->pos_y + maths->raydir_y * maths->perpwalldist;
	texture_cast(data, maths, x);
}

void	raycast_start(t_mlx_data *data)
{
	t_maths	maths;
	int		x;
	int		hit;

	x = 0;
	hit = 0;
	maths.pos_x = data->cub_data->player_x;
	maths.pos_y = data->cub_data->player_y;
	maths.dir_x = data->cub_data->dir_x;
	maths.dir_y = data->cub_data->dir_y;
	maths.plane_x = -maths.dir_y * 0.66;
	maths.plane_y = maths.dir_x * 0.66;
	while (x < data->x)
	{
		ray_loop(data, &maths, x, hit);
		x++;
	}
}
