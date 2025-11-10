/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acolonne <acolonne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 11:21:54 by cabarrou          #+#    #+#             */
/*   Updated: 2025/10/20 16:26:24 by acolonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_bzero(void *s, int n)
{
	int		i;
	char	*res;

	i = 0;
	res = (char *)s;
	while (i < n)
	{
		res[i] = '\0';
		i++;
	}
}

size_t	length(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr(char *s, int c)
{
	int				i;
	char			*res;
	unsigned char	c1;

	i = 0;
	if (!s)
		return (NULL);
	res = (char *)s;
	c1 = (unsigned char)c;
	while (res[i])
	{
		if (res[i] == c1)
			return (&res[i]);
		i++;
	}
	if (c1 == '\0')
		return (&res[i]);
	return (0);
}

char	*join(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	if (!s1 && !s2)
		return (NULL);
	res = malloc(sizeof(char) * (length(s1) + length(s2)) + 1);
	if (!res)
		return (NULL);
	while (s1 && s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	while (s2 && s2[j])
	{
		res[i + j] = s2[j];
		j++;
	}
	res[i + j] = '\0';
	if (s1)
		free(s1);
	return (res);
}
