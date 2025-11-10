/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acolonne <acolonne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 19:15:55 by cabarrou          #+#    #+#             */
/*   Updated: 2025/10/28 14:30:22 by acolonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_empty(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (1);
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != 32)
			return (0);
		i++;
	}
	return (1);
}

int	len_line(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (0);
	while (line[i])
		i++;
	return (i);
}

int	start_map(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == '0' || line[i] == '1')
		return (1);
	return (0);
}
