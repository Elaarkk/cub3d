/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabarrou <cabarrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 14:53:29 by cabarrou          #+#    #+#             */
/*   Updated: 2025/09/30 14:31:57 by cabarrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	verif_valid_char(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	if (!data->map)
		return (1);
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] != ' ' && data->map[i][j] != '0'
				&& data->map[i][j] != '1' && data->map[i][j] != 'N'
				&& data->map[i][j] != 'S' && data->map[i][j] != 'E'
				&& data->map[i][j] != 'W')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	verif_player(t_data *data)
{
	int	i;
	int	j;
	int	nb;

	i = 0;
	nb = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] != '0' && data->map[i][j] != '1'
				&& data->map[i][j] != ' ' && nb == 0)
				nb = 1;
			else if (data->map[i][j] != '0' && data->map[i][j] != '1'
					&& data->map[i][j] != ' ' && nb == 1)
				return (1);
			j++;
		}
		i++;
	}
	if (nb == 0)
		return (1);
	return (0);
}

int	mini_map(t_data *data)
{
	int	i;
	int	j;
	int	nb;

	i = 0;
	nb = 0;
	if (!data->map || !data->map[0])
		return (1);
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == '0')
				nb++;
			j++;
		}
		i++;
	}
	if (nb < 1)
		return (1);
	return (0);
}

void	find_player(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] != '0' && data->map[i][j] != '1')
			{
				data->player_x = (double)j;
				data->player_y = (double)i;
				data->player_orientation = data->map[i][j];
				return ;
			}
			j++;
		}
		i++;
	}
}

int	verify_map(t_data *data)
{
	if (mini_map(data))
	{
		print_error("Invalid map\n");
		return (1);
	}
	if (verif_valid_char(data))
	{
		print_error("Invalid char in map\n");
		return (1);
	}
	if (verif_player(data))
	{
		print_error("Invalid number of players\n");
		return (1);
	}
	find_player(data);
	return (0);
}
