/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_calcul.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlanani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 13:15:14 by rlanani           #+#    #+#             */
/*   Updated: 2022/08/14 13:15:15 by rlanani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	my_color(t_data *data, int x, int y)
{
	char	*dst;
	int		color;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	color = *(unsigned int *)dst;
	return (color);
}

void	draw_sky(t_data *mlx)
{
	int			x;
	int			y;
	long int	hexa;

	x = 0;
	y = 0;
	hexa = mlx->cubed->c_rgb[0] * 256 * 256
		+ mlx->cubed->c_rgb[1] * 256 + mlx->cubed->c_rgb[2];
	while (y < 1024)
	{
		if (y < 510)
			hexa = mlx->cubed->c_rgb[0] * 256 * 256
				+ mlx->cubed->c_rgb[1] * 256 + mlx->cubed->c_rgb[2];
		else
			hexa = mlx->cubed->f_rgb[0] * 256 * 256
				+ mlx->cubed->f_rgb[1] * 256 + mlx->cubed->f_rgb[2];
		my_mlx_pixel_put(mlx, x, y, hexa);
		if (x++ == 1024)
		{
			x = 0;
			y++;
		}
	}
}

void	texel_drawend(t_ray *rc, t_data *img, unsigned int **buffer, int x)
{
	int	y;

	y = rc->drawstart;
	while (y <= rc->drawend)
	{
		rc->texy = (int)rc->texpos & (rc->texheight - 1);
		rc->texpos += rc->step;
		rc->color = my_color(&img->texture[rc->texnum], rc->texx, rc->texy);
		if (rc->side == 0)
		{
			if (rc->raydx > 0)
				rc->color = my_color(&img->texture[2], rc->texx, rc->texy);
			if (rc->raydx < 0)
				rc->color = my_color(&img->texture[3], rc->texx, rc->texy);
		}
		if (rc->side == 1)
		{
			if (rc->raydy > 0)
				rc->color = my_color(&img->texture[0], rc->texx, rc->texy);
			if (rc->raydy < 0)
				rc->color = my_color(&img->texture[1], rc->texx, rc->texy);
		}
		buffer[y][x] = rc->color;
		y++;
	}
}

void	texel(t_ray *rc, t_data *img, unsigned int **buffer, int x)
{
	rc->texnum = img->cubed->map[rc->mapx][rc->mapy] - 1;
	if (rc->side == 0)
		rc->wallx = rc->posy + rc->perpd * rc->raydy;
	else
		rc->wallx = rc->posx + rc->perpd * rc->raydx;
	rc->wallx -= floor((rc->wallx));
	rc->texx = (int)(rc->wallx * (double)(rc->texwidth));
	if (rc->side == 0 && rc->raydx > 0)
		rc->texx = rc->texwidth - rc->texx - 1;
	if (rc->side == 1 && rc->raydy < 0)
		rc->texx = rc->texwidth - rc->texx - 1;
	rc->step = 1.0 * rc->texheight / rc->lineheight;
	rc->texpos = (rc->drawstart - rc->h / 2 + rc->lineheight / 2) * rc->step;
	texel_drawend(rc, img, buffer, x);
}
