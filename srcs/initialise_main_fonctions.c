/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise_main_fonctions.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlanani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 23:10:37 by rlanani           #+#    #+#             */
/*   Updated: 2022/08/14 13:08:26 by rlanani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/cub3d.h"

void	initialize_raycast(t_ray *raycast, t_cub *cub)
{
	orientation(raycast, retrieve_position(raycast, cub));
	raycast->texheight = 64;
	raycast->texwidth = 64;
	raycast->h = 1024;
	raycast->w = 1024;
}

int	initialize_texture(t_data *tex, void *mlx, t_cub cub)
{
	int	i;

	i = 0;
	tex[0].img = mlx_xpm_file_to_image(mlx,
			cub.no_path, &tex[0].img_width, &tex[0].img_height);
	tex[1].img = mlx_xpm_file_to_image(mlx,
			cub.so_path, &tex[1].img_width, &tex[1].img_height);
	tex[2].img = mlx_xpm_file_to_image(mlx,
			cub.ea_path, &tex[2].img_width, &tex[2].img_height);
	tex[3].img = mlx_xpm_file_to_image(mlx,
			cub.we_path, &tex[3].img_width, &tex[3].img_height);
	tex[4].img = mlx_xpm_file_to_image(mlx,
			"./texture/eagle.xpm", &tex[4].img_width, &tex[4].img_height);
	if (!tex[0].img || !tex[1].img || !tex[2].img || !tex[3].img || !tex[4].img)
	{
		while (tex[i++].img)
			if (tex[i].img)
				mlx_destroy_image(mlx, tex[i].img);
		free (tex);
		return (0);
	}
	return (1);
}

int	initialize_data(t_data *img, t_data *tex)
{
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	tex[0].addr = mlx_get_data_addr(tex[0].img, &tex[0].bits_per_pixel,
			&tex[0].line_length, &tex[0].endian);
	tex[1].addr = mlx_get_data_addr(tex[1].img, &tex[1].bits_per_pixel,
			&tex[1].line_length, &tex[1].endian);
	tex[2].addr = mlx_get_data_addr(tex[2].img, &tex[2].bits_per_pixel,
			&tex[2].line_length, &tex[2].endian);
	tex[3].addr = mlx_get_data_addr(tex[3].img, &tex[3].bits_per_pixel,
			&tex[3].line_length, &tex[3].endian);
	tex[4].addr = mlx_get_data_addr(tex[4].img, &tex[4].bits_per_pixel,
			&tex[4].line_length, &tex[4].endian);
	if (!img->addr || !tex[0].addr || !tex[1].addr
		|| !tex[2].addr || !tex[3].addr || !tex[4].addr)
	{
		free (tex);
		return (0);
	}
	return (1);
}

void	initialise_raycasting(t_ray *raycast, t_data *img)
{
	raycasting (raycast, img);
	mlx_put_image_to_window(img->mlx, img->mlx_win, img->img, 0, 0);
	mlx_hook(img->mlx_win, 2, 1L << 0, press, img);
	mlx_loop_hook(img->mlx, render_next_frame, img);
	mlx_hook(img->mlx_win, 3, 1L << 1, release, img);
	mlx_hook(img->mlx_win, 17, 1L << 17, destroy, img);
	mlx_loop(img->mlx);
}

int	initialise_img(t_ray *raycast, t_data *img, t_data *tex, t_cub *cub)
{
	img->mlx = mlx_init();
	if (!img->mlx)
		return (0);
	img->mlx_win = mlx_new_window(img->mlx, 1024, 1024, "Cub3d");
	img->raycast = raycast;
	img->texture = tex;
	img->cubed = cub;
	img->key = 0;
	img->key2 = 0;
	img->key3 = 0;
	img->key4 = 0;
	img->key5 = 0;
	img->key6 = 0;
	img->escape = 0;
	img->img = mlx_new_image(img->mlx, 1024, 1024);
	if (!img->img || !img->mlx_win)
	{
		if (!img->mlx_win)
			mlx_destroy_image(img->mlx, img->img);
		if (!img->img)
			mlx_destroy_window(img->mlx, img->mlx_win);
		mlx_destroy_display(img->mlx);
	}
	return (1);
}
