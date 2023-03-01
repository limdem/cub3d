/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_fonctions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlanani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 23:16:18 by rlanani           #+#    #+#             */
/*   Updated: 2022/08/13 23:16:29 by rlanani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/cub3d.h"

int	press(int key, t_data *img)
{
	if (key == 65363)
		img->key = 1;
	if (key == 65361)
		img->key2 = 1;
	if (key == 119)
		img->key3 = 1;
	if (key == 115)
		img->key4 = 1;
	if (key == 97)
		img->key5 = 1;
	if (key == 100)
		img->key6 = 1;
	if (key == 65307)
		img->escape = 1;
	return (0);
}

int	destroy(t_data *img)
{
	free_parsing(*img->cubed);
	mlx_destroy_image(img->mlx, img->texture[0].img);
	mlx_destroy_image(img->mlx, img->texture[1].img);
	mlx_destroy_image(img->mlx, img->texture[2].img);
	mlx_destroy_image(img->mlx, img->texture[3].img);
	mlx_destroy_image(img->mlx, img->texture[4].img);
	free(img->texture);
	mlx_destroy_image(img->mlx, img->img);
	mlx_destroy_window(img->mlx, img->mlx_win);
	mlx_destroy_display(img->mlx);
	free(img->mlx);
	exit (0);
	return (0);
}

int	release(int key, t_data *img)
{
	if (key == 65363)
		img->key = 0;
	if (key == 65361)
		img->key2 = 0;
	if (key == 119)
		img->key3 = 0;
	if (key == 115)
		img->key4 = 0;
	if (key == 97)
		img->key5 = 0;
	if (key == 100)
		img->key6 = 0;
	return (0);
}

void	key5(t_data *img, double oldposx, double oldposy)
{
	img->raycast->posx = img->raycast->posx - (img->raycast->planx / 10);
	if (!not_wall(img))
	{
		img->raycast->posx = oldposx;
		img->raycast->posy = oldposy;
		return ;
	}
	img->raycast->posy = img->raycast->posy - (img->raycast->plany / 10);
	if (!not_wall(img))
	{
		img->raycast->posx = oldposx;
		img->raycast->posy = oldposy;
		return ;
	}
	raycasting (img->raycast, img);
	mlx_put_image_to_window(img->mlx, img->mlx_win, img->img, 0, 0);
}

void	key6(t_data *img, double oldposx, double oldposy)
{
	img->raycast->posx = img->raycast->posx + (img->raycast->planx / 10);
	if (!not_wall(img))
	{
		img->raycast->posx = oldposx;
		img->raycast->posy = oldposy;
		return ;
	}
	img->raycast->posy = img->raycast->posy + (img->raycast->plany / 10);
	if (!not_wall(img))
	{
		img->raycast->posx = oldposx;
		img->raycast->posy = oldposy;
		return ;
	}
	raycasting (img->raycast, img);
	mlx_put_image_to_window(img->mlx, img->mlx_win, img->img, 0, 0);
}
