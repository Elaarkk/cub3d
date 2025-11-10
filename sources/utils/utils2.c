/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabarrou <cabarrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 15:50:13 by acolonne          #+#    #+#             */
/*   Updated: 2025/10/03 16:12:09 by cabarrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_overflow(long nb)
{
	if (nb < INT_MIN || nb > INT_MAX)
		return (-1);
	return (0);
}

int	ft_atoi(char *nptr)
{
	long long	i;
	long long	number;

	i = 0;
	number = 0;
	if (!nptr)
		return (-1);
	while ((nptr[i] >= 9 && nptr[i] <= 13 && nptr[i] != '\n')
		|| (nptr[i] == 32))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			return (-1);
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		number = (nptr[i++] - 48) + (number * 10);
		if (check_overflow(number) == -1)
			return (-1);
	}
	if (i == 0)
		return (-1);
	return ((int)(number));
}

void	ft_putstrfd(char *s, int fd)
{
	int	i;

	if (!s)
		return ;
	i = ft_strlen(s);
	if (fd != -1)
		write(fd, s, i);
}

void	print_error(char *s)
{
	ft_putstrfd("Error\n", 2);
	ft_putstrfd(s, 2);
}

int	check_line(int fd, char *line, int i)
{
	while (line)
	{
		if (empty(line) == 0)
		{
			end_file(line, fd);
			return (-1);
		}
		free(line);
		line = get_next_line(fd);
		i++;
	}
	return (i);
}
