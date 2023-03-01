/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlanani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 13:07:12 by rlanani           #+#    #+#             */
/*   Updated: 2022/08/28 13:07:45 by rlanani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/cub3d.h"

int	ft_color(t_data *img, int bool)
{
	static int	i = 0;
	static int	j = 0;
	int			colora;

	colora = 0;
	if (!bool)
		return (i = 0);
	if (bool == 4)
	{
		i = 0;
		j = 0;
		return (0);
	}
	if (bool == 3)
	{
		i = -1;
		j++;
	}
	if (j >= 0 && j < img->cubed->lines_nbr
		&& i >= 0 && i < img->cubed->len_max)
		if (img->cubed->map[j][i])
			if (img->cubed->map[j][i] == 1 || img->cubed->map[j][i] == 2)
				colora = (0xADD8E6);
	i++;
	return (colora);
}

void	minimap(t_data *img)
{
	int	y;
	int	x;
	int	color;

	color = 0xADD8E6;
	x = 0;
	y = 0;
	while (y < (img->cubed->lines_nbr) * 10)
	{
		while (x < (img->cubed->len_max - 1) * 10)
		{
			if (x % 10 == 0)
				color = ft_color(img, 6);
			my_mlx_pixel_put(img, x, y, color);
			x++;
		}
		x = 0;
		ft_color(img, 0);
		if (y % 10 == 0 && y != 0)
			ft_color(img, 3);
		y++;
	}
	ft_color(img, 4);
	draw_player(img);
}

void	draw_player(t_data *img)
{
	int	x;
	int	y;

	x = img->raycast->posx * 10;
	y = img->raycast->posy * 10;
	my_mlx_pixel_put(img, y, x + 1, 0x000000FF);
	my_mlx_pixel_put(img, y, x - 1, 0x000000FF);
	my_mlx_pixel_put(img, y + 1, x, 0x000000FF);
	my_mlx_pixel_put(img, y - 1, x, 0x000000FF);
	my_mlx_pixel_put(img, y, x + 2, 0x000000FF);
	my_mlx_pixel_put(img, y, x - 2, 0x000000FF);
	my_mlx_pixel_put(img, y + 2, x, 0x000000FF);
	my_mlx_pixel_put(img, y - 2, x, 0x000000FF);
	my_mlx_pixel_put(img, y, x, 0x000000FF);
}
