/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlanani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 23:32:47 by rlanani           #+#    #+#             */
/*   Updated: 2022/08/28 23:32:54 by rlanani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../mlx_linux/mlx.h"
# include <math.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>

# include <sys/stat.h>
# include <fcntl.h>
# include <limits.h>

# define INVALID_FILE "Error\nEnter: ./cub3d [path to the scene]\n"
# define SEVERAL_CHARACTER "Error\nMap can't contain several character position\n"
# define BUFFER_SIZE 10

typedef struct s_validity_list
{
	int						l_limit;
	int						r_limit;
	int						u_limit;
	int						d_limit;
	struct s_validity_list	*prev;
	struct s_validity_list	*next;
}	t_validity_list;

typedef struct s_validity
{
	int	char_nbr;
	int	char_pos_x;
	int	char_pos_y;
	int	found_wall;
	int	found_void;
	int	valid;
}	t_validity;

typedef struct s_prep_tmp
{
	int	index1;
	int	index2;
	int	save;
}				t_prep_tmp;

typedef struct s_map_line
{
	struct s_map_line	*prev;
	struct s_map_line	*next;
	char				*line;
	int					pursue;
	int					beg;
	int					end;
	int					empty;
}				t_map_line;

typedef struct s_map
{
	t_map_line	*map_line;
	char		**tmp_map;
	int			**final_map;
	int			lines_nbr;
	int			len_max;
}				t_map;

typedef struct s_map_ret
{
	struct s_map_line	map_line;
	struct s_map		map;
	struct s_map_line	*tmp;
	struct s_map_line	*tmp_save;
	char				*tmp_line;
}				t_map_ret;

typedef struct s_ray
{
	double		posx;
	double		posy;
	double		dirx;
	double		diry;
	double		planx;
	double		plany;
	double		raydx;
	double		raydy;
	double		camerax;
	int			mapx;
	int			mapy;
	double		sidedistx;
	double		sidedisty;
	double		deltx;
	double		delty;
	int			stepx;
	int			stepy;
	int			hit;
	int			side;
	double		perpd;
	int			lineheight;
	int			drawstart;
	int			drawend;
	int			x;
	int			w;
	int			h;
	long int	color;
	int			texnum;
	double		wallx;
	int			texx;
	int			texy;
	double		texpos;
	double		step;
	int			texwidth;
	int			texheight;
	int			stop;
}					t_ray;

typedef struct s_data
{
	void			*mlx;
	void			*mlx_win;
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				img_width;
	int				img_height;
	int				calcul;
	t_ray			*raycast;
	unsigned int	**buffer;
	struct s_data	*texture;
	struct s_cub	*cubed;
	int				key;
	int				key2;
	int				key3;
	int				key4;
	int				key5;
	int				key6;
	int				escape;
}				t_data;

typedef struct s_retriever
{
	int		pursue;
	char	*line;
	char	*save;
}				t_retriever;

typedef struct s_cub
{
	int			char_nbr;
	int			direction;
	int			floor_ceiling;
	int			no_count;
	int			so_count;
	int			we_count;
	int			ea_count;
	int			f_count;
	int			c_count;
	int			*f_rgb;
	int			*c_rgb;
	char		*no_path;
	char		*so_path;
	char		*we_path;
	char		*ea_path;
	char		*no_texture;
	char		*so_texture;
	char		*we_texture;
	char		*ea_texture;
	int			empty_line;
	char		*floor;
	char		*ceiling;
	int			**map;
	int			len_max;
	int			lines_nbr;
	char		*line_pointer;
	int			fd;
	t_retriever	retriever;
}				t_cub;

int					invalid_char_pos(t_map map, int index1, int index2);
void				free_tmp_save(t_map_line *tmp_save);
unsigned long long	ft_atoull(const char *nptr);
void				draw_sky(t_data *mlx);
void				my_mlx_pixel_put(t_data *data, int x, int y, int color);
int					my_color(t_data *data, int x, int y);
int					deal_key(int key, t_data *img);
int					destroy(t_data *img);
int					handle_parsing(t_cub *cub, int argc, char *argv[]);
int					parse_cub(t_cub *cub, int argc, char *argv[]);
int					is_empty_column(t_map map, int column);
int					initialize_parsing(t_cub *cub);
int					open_scene_file(int *fd, int argc, char *argv[]);
int					check_scene_file(char *path);
int					check_is_directory(char *path);
int					retrieve_textures(t_cub *cub);
int					get_direction(t_cub *cub, char **line);
int					get_texture(t_cub *cub, char *line);
int					check_pursue_texture(t_cub *cub, int *pursue, char *line);
int					is_empty_line(char *line);
int					is_direction(t_cub *cub, char *line);
int					take_texture(t_cub *cub, char *path);
int					check_texture_path(char *no_path, char *so_path,
						char *ea_path, char *we_path);
int					retrieve_floor_ceiling(t_cub *cub);
int					get_floor_ceiling(t_cub *cub, char **line);
int					get_color(t_cub *cub, char *line);
int					check_pursue_floor_ceiling(t_cub *cub, int *pursue);
int					is_floor_ceiling(t_cub *cub, char *line);
int					handle_get_number(t_cub *cub, char *tmp, char *save);
int					get_number(t_cub *cub, char **line, int index, char *save);
int					go_to_next_number(char **line, char **save);
int					go_to_next_number_index2(char **line, char **save);
int					take_color(char *color, int *i, int index, char *save);
int					check_number(char *color, unsigned long long number,
						int index, char *save);
void				take_number(t_cub *cub, unsigned long long number,
						int index);
int					move_to_number(char *color, int *index);
int					retrieve_map(t_cub *cub);
void				prepare_map(t_map *map, t_map_line *map_line,
						t_map_line **tmp, char	**tmp_line);
int					check_map_lines(t_map map, char *tmp_line,
						t_map_line *map_line, t_map_line *tmp_save);
int					create_map_line(t_map map, t_map_line map_line,
						t_map_line **tmp, char *tmp_line);
int					create_tmp_map(t_map *map);
int					get_final_map(t_cub *cub, t_map *map);
int					check_pursue_map_lines(char *line, t_map_line *map_line);
int					prepare_tmp_map(t_map *map, t_map_line **tmp);
int					fill_tmp_map(t_map **map, t_map_line**tmp,
						t_prep_tmp *prep_map);
int					check_map_validity(t_map map);
int					convert_to_final_map(t_cub *cub, t_map *map);
int					fill_final_map(t_cub *cub, t_map *map,
						int start, int index);
int					handle_char_pos(char el, int *char_pos, int *char_nbr);
int					finalize_final_map(t_cub *cub, t_map *map);
int					is_closed(t_map map, int index1, int index2);
int					invalid_el(char el);
void				determine_start(t_cub *cub, t_map *map,
						int *start, int *index);
void				free_tmp_map(t_map map);
void				free_tmp_map_line1(t_map map, char *line,
						char *line_pointer);
void				free_lines(t_map map);
void				free_map_line(t_map map);
void				error_free_final_map(int **map, int index);
void				free_tmp_map_line(t_map map);
void				free_parsing(t_cub cub);
void				error_free_parse_cub(t_cub cub);
char				*get_next_line(int fd, char **line_saver);
char				*save_next_line(char *str);
char				*get_line(char *str);
char				*custom_join(char *dest, char *src);
int					ft_strlen(const char *s);
int					is_current_line(char *str, int reader);
void				*ft_memmove(void *dest, const void *src, int n);
void				ft_putstr_fd(char *s, int fd);
char				*ft_strtrim(char const *s1);
char				*ft_strdup(const char *s);
int					ft_isspace(char c);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_isdigit(int c);
char				*strtrim_end(char const *s1);
void				*ft_memset(void *s, int c, size_t n);
char				*to_free(char *pt);
int					raycasting(t_ray *raycast, t_data *img);
int					deal_key(int key, t_data *img);
int					destroy(t_data *img);
int					render_next_frame(t_data *img);
void				draw_buffer(t_data *img, unsigned int **buffer);
void				free_buffer(unsigned int **buffer);
int					initialize_main_parsing(t_cub *cub, int argc, char **argv);
int					initialize_texture(t_data *texture, void *mlx,
						t_cub	cub);
int					initialize_data(t_data *img, t_data *texture);
void				initialise_raycasting(t_ray *raycast, t_data *img);
int					initialise_img(t_ray *raycast, t_data *img,
						t_data *texture, t_cub *cub);
int					release(int key, t_data *img);
void				initialize_raycast(t_ray *raycast, t_cub *cub);
int					release(int key, t_data *img);
int					destroy(t_data *img);
int					press(int key, t_data *img);
void				texel(t_ray *rc, t_data *img, unsigned int **buffer, int x);
void				texel_drawend(t_ray *rc, t_data *img,
						unsigned int **buffer, int x);
void				key5(t_data *img, double oldposx, double oldposy);
void				key6(t_data *img, double oldposx, double oldposy);
int					retrieve_position(t_ray *raycast, t_cub *cub);
int					orientation(t_ray *raycast, int position);
int					east(t_ray *raycast);
int					north(t_ray *raycast);
int					south(t_ray *raycast);
int					west(t_ray *raycast);
int					not_wall(t_data *img);
void				minimap(t_data *img);
int					ft_color(t_data *img, int bool);
void				draw_player(t_data *img);
void				ft_putnbr_base(long int nbr, char *base);

#endif
