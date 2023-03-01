/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retrieve_position.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlanani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 20:35:35 by rlanani           #+#    #+#             */
/*   Updated: 2022/08/20 20:35:37 by rlanani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/cub3d.h"

int	retrieve_position(t_ray *raycast, t_cub *cub)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < cub->lines_nbr)
	{
		while (i < cub->len_max - 1)
		{
			if (cub->map[j][i] > 2)
			{
				raycast->posx = j + 0.5;
				raycast->posy = i + 0.5;
				return (cub->map[j][i]);
			}
			i++;
		}
		i = 0;
		j++;
	}
	return (1);
}

int	orientation(t_ray *raycast, int position)
{
	raycast->dirx = -1;
	raycast->diry = 0;
	raycast->planx = 0;
	raycast->plany = 0.66;
	if (position == 5)
		south(raycast);
	if (position == 3)
		north(raycast);
	if (position == 6)
		east(raycast);
	return (1);
}
