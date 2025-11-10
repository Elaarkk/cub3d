/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabarrou <cabarrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 18:19:14 by acolonne          #+#    #+#             */
/*   Updated: 2025/10/03 13:43:48 by cabarrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	cell_and_floor(int x, int start, int end, t_mlx_data *data)
{
	int	i;

	i = 0;
	while (i < start)
	{
		my_mlx_pixel_put(data, x, i, data->cub_data->c);
		i++;
	}
	i = end;
	while (i < data->y)
	{
		my_mlx_pixel_put(data, x, i, data->cub_data->f);
		i++;
	}
}

void	render_calc(t_mlx_data *data, t_maths *maths, int x)
{
	if (maths->side == 1 && maths->hit_y < maths->pos_y)
		maths->texnum = 0;
	else if (maths->side == 1 && maths->hit_y >= maths->pos_y)
		maths->texnum = 1;
	else if (maths->side == 0 && maths->hit_x >= maths->pos_x)
		maths->texnum = 2;
	else
		maths->texnum = 3;
	maths->lineheight = (int)(data->y / maths->perpwalldist);
	maths->drawstart = -maths->lineheight / 2 + data->y / 2;
	if (maths->drawstart < 0)
		maths->drawstart = 0;
	maths->drawend = maths->lineheight / 2 + data->y / 2;
	if (maths->drawend >= data->y)
		maths->drawend = data->y - 1;
	cell_and_floor(x, maths->drawstart, maths->drawend, data);
	if (maths->side == 0)
		maths->wall_x = maths->pos_y + maths->perpwalldist * maths->raydir_y;
	else
		maths->wall_x = maths->pos_x + maths->perpwalldist * maths->raydir_x;
	maths->wall_x -= floor(maths->wall_x);
}

void	put_textures(t_mlx_data *data, t_maths *maths, int x, int y)
{
	while (y < maths->drawend)
	{
		maths->tex_y = (int)maths->texpos & (64 - 1);
		maths->texpos += maths->step;
		maths->color = data->tex[maths->texnum][64
			* maths->tex_y + maths->tex_x];
		if (maths->side == 1)
			maths->color = (maths->color >> 1) & 8355711;
		my_mlx_pixel_put(data, x, y, maths->color);
		y++;
	}
}

void	texture_cast(t_mlx_data *data, t_maths *maths, int x)
{
	int	y;

	render_calc(data, maths, x);
	maths->tex_x = (int)(maths->wall_x * (double)64);
	if (maths->side == 0 && maths->raydir_x > 0)
		maths->tex_x = 64 - maths->tex_x - 1;
	if (maths->side == 1 && maths->raydir_y < 0)
		maths->tex_x = 64 - maths->tex_x - 1;
	maths->step = 1.0 * 64 / maths->lineheight;
	maths->texpos = (maths->drawstart - 600 / 2 + maths->lineheight / 2)
		* maths->step;
	y = maths->drawstart;
	maths->tex_x = abs(64 - maths->tex_x);
	put_textures(data, maths, x, y);
}
