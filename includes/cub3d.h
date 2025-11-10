/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acolonne <acolonne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 19:28:29 by cabarrou          #+#    #+#             */
/*   Updated: 2025/10/28 14:26:04 by acolonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
# include "./gnl.h"
# include <limits.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

enum				e_key
{
	w_key = 0,
	a_key = 1,
	d_key = 2,
	s_key = 3,
	right_arrow = 4,
	left_arrow = 5,
	shift = 6
};

typedef struct s_data
{
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	long			f;
	long			c;
	char			**map;
	char			player_orientation;
	double			dir_x;
	double			dir_y;
	double			player_x;
	double			player_y;
	double			plane_x;
	double			plane_y;
}					t_data;

typedef struct s_mlx_data
{
	void			*mlx_ptr;
	void			*win_ptr;
	void			**img;
	void			*big_img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				x;
	int				y;
	int				keycode[7];
	int				tile_size;
	int				*tex[4];
	int				tex_width;
	int				tex_heigth;
	int				size_line;

	t_data			*cub_data;
}					t_mlx_data;

/*
	// double			old_time;
	// double			current_time;
	// double			frame_time;
*/

typedef struct s_maths
{
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	double			camera_x;
	double			raydir_x;
	double			raydir_y;
	int				map_x;
	int				map_y;
	double			sidedist_x;
	double			sidedist_y;
	double			deltadist_x;
	double			deltadist_y;
	double			perpwalldist;
	int				step_x;
	int				step_y;
	int				side;
	double			hit_x;
	double			hit_y;
	double			wall_x;
	int				tex_x;
	double			step;
	double			texpos;
	int				y;
	int				tex_y;
	unsigned int	color;
	int				lineheight;
	int				drawstart;
	int				drawend;
	int				texnum;

}					t_maths;

typedef struct s_minimap
{
	double	x;
	double	y;
	double	offset_x;
	double	offset_y;
}				t_minimap;

int					parsing(char *file, t_data *data);

int					len_line(char *line);

void				print_error(char *s);

char				*get_next_line(int fd);

void				free_all(t_data *data);

int					ft_strlen(char *s);

void				*ft_calloc(size_t nmemb, size_t size);

int					ft_strncmp(const char *s1, const char *s2, size_t n);

int					ft_atoi(char *nptr);

unsigned long		create_rgb(int r, int g, int b);

int					check_empty(char *line);

int					get_textures(int fd, t_data *data);

int					start_map(char *line);

int					get_map(t_data *data, int fd, char *file);

int					verify_map(t_data *data);

int					verify_texture(t_data *data);

int					check_filename(char *file, char *filename);

int					data_init(t_data *cub_data);

int					close_window(t_mlx_data *data);

void				free_mlx(t_mlx_data *data);

void				draw_player(t_mlx_data *data);

void				draw_map(t_mlx_data *data);

int					on_press(int keycode, t_mlx_data *data);

int					on_release(int keycode, t_mlx_data *data);

int					refresh(t_mlx_data *data);

void				my_mlx_pixel_put(t_mlx_data *data, int x, int y, int color);

void				raycast_start(t_mlx_data *data);

int					draw_player_square(t_mlx_data *data, int x, int y,
						int color);

int					check_walls(t_data *data);

double				get_time(void);

void				texture_cast(t_mlx_data *data, t_maths *maths, int x);

void				end_file(char *line, int fd);

void				init_keycode(t_mlx_data *data);

void				player_movements(t_mlx_data *data);

int					check_line(int fd, char *line, int i);

int					empty(char *line);

#endif