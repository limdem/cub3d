/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgauvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 05:40:52 by dgauvin           #+#    #+#             */
/*   Updated: 2022/08/28 05:44:46 by dgauvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	not_wall(t_data *img)
{
	int	x;
	int	y;

	x = (int)img->raycast->posx;
	y = (int)img->raycast->posy;
	if (img->cubed->map[x][y] == 1)
		return (0);
	return (1);
}
