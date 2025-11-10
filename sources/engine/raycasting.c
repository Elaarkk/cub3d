/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabarrou <cabarrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 18:51:19 by acolonne          #+#    #+#             */
/*   Updated: 2025/10/03 17:30:14 by cabarrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ray_projection_init(t_mlx_data *data)
{
	if (data->cub_data->player_orientation == 'W')
	{
		data->cub_data->dir_x = -1;
		data->cub_data->dir_y = 0;
	}
	if (data->cub_data->player_orientation == 'E')
	{
		data->cub_data->dir_x = 1;
		data->cub_data->dir_y = 0;
	}
	if (data->cub_data->player_orientation == 'N')
	{
		data->cub_data->dir_x = 0;
		data->cub_data->dir_y = -1;
	}
	if (data->cub_data->player_orientation == 'S')
	{
		data->cub_data->dir_x = 0;
		data->cub_data->dir_y = 1;
	}
}

int	single_tex(t_mlx_data *data, int index, char *dir)
{
	data->img[index] = mlx_xpm_file_to_image(data->mlx_ptr, dir,
			&data->tex_width, &data->tex_heigth);
	if (!data->img[index])
	{
		print_error("Texture Error\n");
		return (1);
	}
	data->tex[index] = (int *)mlx_get_data_addr(data->img[index],
			&data->bits_per_pixel, &data->size_line, &data->endian);
	return (0);
}

int	init_texture(t_mlx_data *data)
{
	data->img = malloc(sizeof(void *) * 4);
	if (!data->img)
		return (1);
	if (single_tex(data, 0, data->cub_data->no) != 0)
		return (1);
	if (single_tex(data, 1, data->cub_data->so) != 0)
		return (1);
	if (single_tex(data, 2, data->cub_data->we) != 0)
		return (1);
	if (single_tex(data, 3, data->cub_data->ea) != 0)
		return (1);
	return (0);
}

void	mlx_start(t_mlx_data data)
{
	draw_map(&data);
	draw_player(&data);
	ray_projection_init(&data);
	raycast_start(&data);
	mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.big_img, 0, 0);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &on_press, &data);
	mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, &on_release, &data);
	mlx_hook(data.win_ptr, 17, 0, &close_window, &data);
	mlx_loop_hook(data.mlx_ptr, &refresh, &data);
	mlx_loop(data.mlx_ptr);
}

/*
data.current_time = get_time();
data.old_time = data.current_time;
*/

int	data_init(t_data *cub_data)
{
	t_mlx_data	data;

	data.x = 800;
	data.y = 600;
	data.tile_size = 10;
	cub_data->player_x += 0.5;
	cub_data->player_y += 0.5;
	data.cub_data = cub_data;
	init_keycode(&data);
	data.mlx_ptr = NULL;
	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		return (1);
	data.win_ptr = mlx_new_window(data.mlx_ptr, data.x, data.y, "cub3D");
	if (data.win_ptr == NULL)
		return (1);
	if (init_texture(&data) != 0)
		return (1);
	data.big_img = mlx_new_image(data.mlx_ptr, data.x, data.y);
	data.addr = mlx_get_data_addr(data.big_img, &data.bits_per_pixel,
			&data.line_length, &data.endian);
	mlx_start(data);
	return (0);
}
