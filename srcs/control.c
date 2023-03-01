/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlanani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 13:32:44 by rlanani           #+#    #+#             */
/*   Updated: 2022/08/28 05:41:36 by dgauvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/cub3d.h"

void	key1(t_data *img)
{
	double	oldplanex;
	double	olddirx;

	olddirx = img->raycast->dirx;
	oldplanex = img->raycast->planx;
	img->raycast->dirx = img->raycast->dirx * cos(-0.033 * 1.8 / 2)
		- img->raycast->diry * sin(-0.033 * 1.8 / 2);
	img->raycast->diry = olddirx * sin(-0.033 * 1.8 / 2)
		+ img->raycast->diry * cos(-0.033 * 1.8 / 2);
	img->raycast->planx = img->raycast->planx * cos(-0.033 * 1.8 / 2)
		- img->raycast->plany * sin(-0.033 * 1.8 / 2);
	img->raycast->plany = oldplanex * sin(-0.033 * 1.8 / 2)
		+ img->raycast->plany * cos(-0.033 * 1.8 / 2);
	if (!not_wall(img))
	{
		img->raycast->dirx = olddirx;
		img->raycast->planx = oldplanex;
		return ;
	}
	raycasting (img->raycast, img);
	mlx_put_image_to_window(img->mlx, img->mlx_win, img->img, 0, 0);
}

void	key2(t_data *img)
{
	double	oldplanex;
	double	olddirx;

	olddirx = img->raycast->dirx;
	oldplanex = img->raycast->planx;
	img->raycast->dirx = img->raycast->dirx * cos(0.033 * 1.8 / 2)
		- img->raycast->diry * sin(0.033 * 1.8 / 2);
	img->raycast->diry = olddirx * sin(0.033 * 1.8 / 2)
		+ img->raycast->diry * cos(0.033 * 1.8 / 2);
	img->raycast->planx = img->raycast->planx * cos(0.033 * 1.8 / 2)
		- img->raycast->plany * sin(0.033 * 1.8 / 2);
	img->raycast->plany = oldplanex * sin(0.033 * 1.8 / 2)
		+ img->raycast->plany * cos(0.033 * 1.8 / 2);
	if (!not_wall(img))
	{
		img->raycast->dirx = olddirx;
		oldplanex = oldplanex;
		return ;
	}
	raycasting (img->raycast, img);
	mlx_put_image_to_window(img->mlx, img->mlx_win, img->img, 0, 0);
}

void	key3(t_data *img, double oldposx, double oldposy)
{
	img->raycast->posx = img->raycast->posx + (img->raycast->dirx / 10);
	if (!not_wall(img))
	{
		img->raycast->posx = oldposx;
		img->raycast->posy = oldposy;
		return ;
	}
	img->raycast->posy = img->raycast->posy + (img->raycast->diry / 10);
	if (!not_wall(img))
	{
		img->raycast->posx = oldposx;
		img->raycast->posy = oldposy;
		return ;
	}
	raycasting (img->raycast, img);
	mlx_put_image_to_window(img->mlx, img->mlx_win, img->img, 0, 0);
}

void	key4(t_data *img, double oldposx, double oldposy)
{
	img->raycast->posx = img->raycast->posx - (img->raycast->dirx / 10);
	if (!not_wall(img))
	{
		img->raycast->posx = oldposx;
		img->raycast->posy = oldposy;
		return ;
	}
	img->raycast->posy = img->raycast->posy - (img->raycast->diry / 10);
	if (!not_wall(img))
	{
		img->raycast->posx = oldposx;
		img->raycast->posy = oldposy;
		return ;
	}
	raycasting (img->raycast, img);
	mlx_put_image_to_window(img->mlx, img->mlx_win, img->img, 0, 0);
}

int	render_next_frame(t_data *img)
{
	double	oldposx;
	double	oldposy;

	oldposx = img->raycast->posx;
	oldposy = img->raycast->posy;
	if (img->escape == 1)
		destroy(img);
	if (img->key == 1)
		key1(img);
	if (img->key2 == 1)
		key2(img);
	if (img->key3 == 1)
		key3(img, oldposx, oldposy);
	if (img->key4 == 1)
		key4(img, oldposx, oldposy);
	if (img->key5 == 1)
		key5(img, oldposx, oldposy);
	if (img->key6 == 1)
		key6(img, oldposx, oldposy);
	return (1);
}
