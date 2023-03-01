/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlanani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 16:40:49 by rlanani           #+#    #+#             */
/*   Updated: 2022/08/07 16:43:57 by rlanani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/cub3d.h"

int	dda_hit(t_ray *rc, t_data *img)
{
	while (rc->hit == 0)
	{
		if (rc->sidedistx < rc->sidedisty)
		{
			rc->sidedistx += rc->deltx;
			rc->mapx += rc->stepx;
			rc->side = 0;
		}
		else
		{
			rc->sidedisty += rc->delty;
			rc->mapy += rc->stepy;
			rc->side = 1;
		}
		if (img->cubed->map[rc->mapx][rc->mapy] == 1)
			rc->hit = 1;
	}
	return (1);
}

int	dda(t_ray *rc, t_data *img, int x)
{
	dda_hit(rc, img);
	if (rc->side == 0)
		rc->perpd = (rc->sidedistx - rc->deltx);
	else
		rc->perpd = (rc->sidedisty - rc->delty);
	if (rc->side == 0)
		rc->perpd = (rc->sidedistx - rc->deltx);
	else
		rc->perpd = (rc->sidedisty - rc->delty);
	rc->lineheight = (int)(rc->h / rc->perpd);
	rc->drawstart = -rc->lineheight / 2 + rc->h / 2;
	if (rc->drawstart < 0)
		rc->drawstart = 0;
	rc->drawend = rc->lineheight / 2 + rc->h / 2;
	if (rc->drawend >= rc->h)
		rc->drawend = rc->h - 1;
	x++;
	return (1);
}

void	inside_rc(t_ray *rc)
{
	if (rc->raydx < 0)
	{
		rc->stepx = -1;
		rc->sidedistx = (rc->posx - rc->mapx) * rc->deltx;
	}
	else
	{
		rc->stepx = 1;
		rc->sidedistx = (rc->mapx + 1.0 - rc->posx) * rc->deltx;
	}
	if (rc->raydy < 0)
	{
		rc->stepy = -1;
		rc->sidedisty = (rc->posy - rc->mapy) * rc->delty;
	}
	else
	{
		rc->stepy = 1;
		rc->sidedisty = (rc->mapy + 1.0 - rc->posy) * rc->delty;
	}
}

int	launch_raycasting(t_ray *rc, t_data *img)
{
	int	x;

	x = 0;
	while (x < rc->w)
	{
		rc->camerax = 2 * x / (double)rc->w - 1;
		rc->raydx = rc->dirx + rc->planx * rc->camerax;
		rc->raydy = rc->diry + rc->plany * rc->camerax;
		rc->mapx = (int)(rc->posx);
		rc->mapy = (int)(rc->posy);
		rc->deltx = fabs(1 / rc->raydx);
		rc->delty = fabs(1 / rc->raydy);
		rc->hit = 0;
		inside_rc(rc);
		if (!dda(rc, img, x))
		{
			free_buffer(img->buffer);
			return (0);
		}
		texel(rc, img, img->buffer, x);
		x++;
	}
	return (1);
}

int	raycasting(t_ray *rc, t_data *img)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	img->buffer = malloc(sizeof(unsigned int *) * 1024);
	while (i < 1024)
	{
		img->buffer[i] = malloc(sizeof(unsigned int) * 1024);
		while (j < 1024)
		{
			img->buffer[i][j] = 0;
			j++;
		}
		j = 0;
		i++;
	}
	if (!launch_raycasting(rc, img))
		return (0);
	draw_buffer(img, img->buffer);
	minimap(img);
	free_buffer(img->buffer);
	return (1);
}
