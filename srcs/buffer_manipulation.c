/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_manipulation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlanani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 17:18:05 by rlanani           #+#    #+#             */
/*   Updated: 2022/08/12 17:18:06 by rlanani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/cub3d.h"

void	draw_buffer(t_data *img, unsigned int **buffer)
{
	int	y;
	int	x;

	x = 0;
	y = 0;
	draw_sky(img);
	while (y < 1024)
	{
		if (y >= 0)
		{
			while (x < 1024)
			{
				if (buffer[y][x] != 0)
					my_mlx_pixel_put(img, x, y, buffer[y][x]);
				x++;
			}
		}
		x = 0;
		y++;
	}
}

void	free_buffer(unsigned int **buffer)
{
	int	i;

	i = 0;
	while (i < 1024)
	{
		free(buffer[i]);
		i++;
	}
	free(buffer);
}

unsigned int	**malloc_buffer(unsigned int ***buffer)
{
	int	i;
	int	j;

	*buffer = malloc(sizeof(unsigned int *) * 1024);
	while (i < 1024)
	{
		*buffer[i] = malloc(sizeof(unsigned int) * 1024);
		while (j < 1024)
		{
			*buffer[i][j] = 0;
			j++;
		}
		j = 0;
		i++;
	}
	return (*buffer);
}
