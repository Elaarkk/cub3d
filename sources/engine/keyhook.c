/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acolonne <acolonne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 16:35:46 by acolonne          #+#    #+#             */
/*   Updated: 2025/09/30 16:38:28 by acolonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	on_press_rotation(int keycode, t_mlx_data *data)
{
	if (keycode == XK_Right)
	{
		data->keycode[right_arrow] = 1;
	}
	if (keycode == XK_Left)
	{
		data->keycode[left_arrow] = 1;
	}
}

int	on_press(int keycode, t_mlx_data *data)
{
	if (keycode == 'w')
	{
		data->keycode[w_key] = 1;
	}
	if (keycode == 'a')
	{
		data->keycode[a_key] = 1;
	}
	if (keycode == 'd')
	{
		data->keycode[d_key] = 1;
	}
	if (keycode == 's')
	{
		data->keycode[s_key] = 1;
	}
	if (keycode == XK_Shift_L)
	{
		data->keycode[shift] = 1;
	}
	on_press_rotation(keycode, data);
	return (0);
}

void	on_release_rotation(int keycode, t_mlx_data *data)
{
	if (keycode == XK_Right)
	{
		data->keycode[right_arrow] = 0;
	}
	if (keycode == XK_Left)
	{
		data->keycode[left_arrow] = 0;
	}
	if (keycode == XK_Shift_L)
	{
		data->keycode[shift] = 0;
	}
}

int	on_release(int keycode, t_mlx_data *data)
{
	if (keycode == XK_Escape)
	{
		free_mlx(data);
		free_all((data->cub_data));
		exit(1);
	}
	if (keycode == 'w')
	{
		data->keycode[w_key] = 0;
	}
	if (keycode == 'a')
	{
		data->keycode[a_key] = 0;
	}
	if (keycode == 'd')
	{
		data->keycode[d_key] = 0;
	}
	if (keycode == 's')
	{
		data->keycode[s_key] = 0;
	}
	on_release_rotation(keycode, data);
	return (0);
}
