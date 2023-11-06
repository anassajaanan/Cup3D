/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 13:36:41 by aajaanan          #+#    #+#             */
/*   Updated: 2023/11/06 05:12:11 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <limits.h>
# include <sys/errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/uio.h>
# include "../lib/libft/include/libft.h"
# include "../lib/mlx/mlx.h"


#define WINDOW_WIDTH 2048
#define WINDOW_HEIGHT 1024

typedef enum e_error
{
	SUCCESS,
	INVALID_ARG,
	WRONG_MAP,
	WRONG_INPUT,
	MALLOC_FAIL,
	IMG_FAIL,
	OPEN_ERR,
	MLX_FAIL,
	WRITE_FAIL,
	WRONG_TEXTURE
}					t_error;


// #===========# queue.c #===============#
typedef struct s_queue_node
{
	char				*val;
	struct s_queue_node	*next;
}						t_queue_node;

typedef struct s_queue
{
	t_queue_node		*front;
	t_queue_node		*rear;
}						t_queue;

void					init_queue(t_queue *q);
void					enqueue(t_queue *q, void *val);
void					*dequeue(t_queue *q);
char					*queue_to_str(t_queue *q);
void					free_queue(t_queue *q);
// #===========# queue.c #===============#


// #===========# parsing.c #=============#

typedef struct s_color
{
	int	red;
	int green;
	int blue;
}		t_color;

typedef struct s_map_infos
{
	char		*no_path;
	char		*so_path;
	char		*we_path;
	char		*ea_path;
	
	t_color		floor_color;
	t_color		ceiling_color;

	t_queue		queue;

	int			parsed_color_count;
	int			parsed_texture_count;
}				t_map_infos;

typedef struct s_map
{
	int		cols;
	int		rows;
	char	**map_data;
}			t_map;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;	
	int		bpp;	
	int		line_length;
	int		endian;
	int		width;
	int		height;
}			t_img;

typedef struct s_player
{
	double	x;
	double	y;
	double	dx;
	double	dy;
	double	direction;
}			t_player;

typedef struct s_ray
{
	double	x;
	double	y;
	double	length;
	int		hit;
}			t_ray;


typedef struct s_params
{
	void		*mlx;
	void		*win;
	t_img		window_img;
	
	t_map		map;
	t_map_infos	map_infos;
	
	t_player	player;
	t_ray		ray;

	
	t_img		north_texture;
	t_img		south_texture;
	t_img		west_texture;
	t_img		east_texture;
	
}				t_params;



// #============# free.c #===============#
void	ft_free(void *ptr);
void	free_split_array(char **array);

// #============# utils.c #===============#
int	is_numeric(char *str);

// #============# parsing.c #===============#
int	parse_map(char *file_name, t_map_infos *map_infos);

// #============# parsing_validation.c #===============#
int	validate_colors(t_map_infos *map_infos, t_color *color, char **colors);
int	is_valid_texture_path(char *path);

// #============# parsing_helpers.c #===============#
int startswith(char **array, char *str);
int	array_size(char **array);
int	is_empty_line(char *line);
int open_map_file(char *file_name);

// #============# map_validation.c #===============#
int	is_valid_map(t_map *map);


// #============# init.c #===============#
void	init_map_infos(t_map_infos *map_infos);

#endif /* CUB3D_H */