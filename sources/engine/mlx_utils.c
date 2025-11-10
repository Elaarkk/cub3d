/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabarrou <cabarrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 19:03:03 by acolonne          #+#    #+#             */
/*   Updated: 2025/10/03 18:35:29 by cabarrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	my_mlx_pixel_put(t_mlx_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x > data->x)
		return ;
	if (y < 0 || y > data->y)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	free_mlx(t_mlx_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_image(data->mlx_ptr, data->big_img);
	mlx_destroy_image(data->mlx_ptr, data->img[0]);
	mlx_destroy_image(data->mlx_ptr, data->img[1]);
	mlx_destroy_image(data->mlx_ptr, data->img[2]);
	mlx_destroy_image(data->mlx_ptr, data->img[3]);
	free(data->img);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
}

int	close_window(t_mlx_data *data)
{
	free_mlx(data);
	free_all((data->cub_data));
	exit(1);
}
