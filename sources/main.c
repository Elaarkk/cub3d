/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acolonne <acolonne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 19:28:43 by cabarrou          #+#    #+#             */
/*   Updated: 2025/10/20 16:36:51 by acolonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	cub(char **argv, t_data *cub_data)
{
	if (parsing(argv[1], cub_data))
	{
		free_all(cub_data);
		return (1);
	}
	if (data_init(cub_data))
	{
		free_all(cub_data);
		print_error("MLX Error\n");
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	*cub_data;

	cub_data = ft_calloc(sizeof(t_data), 1);
	if (!cub_data)
		return (1);
	cub_data->f = -1;
	cub_data->c = -1;
	cub_data->player_x = 0;
	cub_data->player_y = 0;
	if (argc != 2)
	{
		free_all(cub_data);
		print_error("Wrong arguments number\n");
		return (1);
	}
	if (cub(argv, cub_data))
		return (1);
	free_all(cub_data);
	return (0);
}
