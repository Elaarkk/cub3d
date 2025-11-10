/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabarrou <cabarrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 11:16:04 by cabarrou          #+#    #+#             */
/*   Updated: 2024/12/11 19:56:44 by cabarrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	*fill(int fd, char *txt_lu)
{
	char	*buffer;
	int		nbbyte;

	nbbyte = 1;
	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	ft_bzero(buffer, BUFFER_SIZE + 1);
	while (!ft_strchr(txt_lu, '\n') && nbbyte > 0)
	{
		nbbyte = read(fd, buffer, BUFFER_SIZE);
		if (nbbyte < 0)
		{
			free(txt_lu);
			free(buffer);
			return (NULL);
		}
		buffer[nbbyte] = '\0';
		txt_lu = join(txt_lu, buffer);
	}
	free(buffer);
	return (txt_lu);
}

char	*find_line(char *txt_lu)
{
	char	*line;
	int		len_l;
	int		i;

	len_l = 0;
	i = 0;
	if (!txt_lu[i])
		return (NULL);
	while (txt_lu[len_l] != '\n' && txt_lu[len_l] != '\0')
		len_l++;
	line = malloc(sizeof(char) * len_l + 2);
	if (!line)
		return (NULL);
	while (i < len_l)
	{
		line[i] = txt_lu[i];
		i++;
	}
	if (txt_lu[len_l] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*cutline(char *txt_lu)
{
	char	*reste;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!txt_lu)
		return (NULL);
	while (txt_lu[i] && txt_lu[i] != '\n')
		i++;
	if (txt_lu[i] == '\0')
	{
		free(txt_lu);
		return (NULL);
	}
	reste = malloc(sizeof(char) * (length(txt_lu) - i + 1));
	if (!reste)
		return (NULL);
	i++;
	while (txt_lu[i])
		reste[j++] = txt_lu[i++];
	reste[j] = '\0';
	free(txt_lu);
	return (reste);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*txt_lu;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!txt_lu)
	{
		txt_lu = malloc(sizeof(char) * 1);
		if (!txt_lu)
			return (NULL);
		ft_bzero(txt_lu, 1);
	}
	txt_lu = fill(fd, txt_lu);
	if (!txt_lu)
		return (NULL);
	line = find_line(txt_lu);
	txt_lu = cutline(txt_lu);
	return (line);
}
