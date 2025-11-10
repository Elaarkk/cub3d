/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acolonne <acolonne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 20:46:23 by acolonne          #+#    #+#             */
/*   Updated: 2025/10/20 16:29:30 by acolonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*s1_cpy;
	unsigned char	*s2_cpy;

	s1_cpy = (unsigned char *)s1;
	s2_cpy = (unsigned char *)s2;
	i = 0;
	while ((s1_cpy[i] || s2_cpy[i]) && (i < n))
	{
		if (s1_cpy[i] > s2_cpy[i])
			return (1);
		if (s1_cpy[i] < s2_cpy[i])
			return (-1);
		i++;
	}
	return (0);
}

void	free_map(char **split)
{
	int	i;

	i = 0;
	while (split && split[i])
	{
		if (split[i])
			free(split[i]);
		i++;
	}
	if (split)
		free(split);
}

void	free_textures(t_data *data)
{
	if (data->so)
		free(data->so);
	if (data->no)
		free(data->no);
	if (data->ea)
		free(data->ea);
	if (data->we)
		free(data->we);
}

void	free_all(t_data *data)
{
	free_textures(data);
	free_map(data->map);
	if (data)
		free(data);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t			i;
	unsigned char	*memory;

	i = 0;
	memory = malloc(nmemb * size);
	if (!memory)
		return (0);
	while (i < (nmemb * size))
	{
		memory[i] = 0;
		i++;
	}
	return (memory);
}
