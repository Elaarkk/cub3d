/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabarrou <cabarrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 21:30:05 by cabarrou          #+#    #+#             */
/*   Updated: 2025/10/03 13:43:13 by cabarrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GNL_H
# define GNL_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 48
# endif

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

void	ft_bzero(void *s, int n);

size_t	length(char *s);

char	*ft_strchr(char *s, int c);

char	*join(char *s1, char *s2);

char	*get_next_line(int fd);

#endif
