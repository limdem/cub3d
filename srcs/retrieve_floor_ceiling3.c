/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retrieve_floor_ceiling3.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgauvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 01:04:07 by dgauvin           #+#    #+#             */
/*   Updated: 2022/08/10 01:04:46 by dgauvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	move_to_number(char *color, int *index)
{
	while (color[*index])
	{
		if (!ft_isdigit(color[*index]))
		{
			if ((color[*index] == ',' && *index > 0)
				|| ft_isspace(color[*index]))
				break ;
			return (1);
		}
		(*index)++;
	}
	if (!*index)
		return (1);
	return (0);
}

void	take_number(t_cub *cub, unsigned long long number, int index)
{
	if (cub->floor_ceiling == 1)
	{
		cub->f_rgb[index] = (int) number;
		cub->f_count++;
	}
	else
	{
		cub->c_rgb[index] = (int) number;
		cub->c_count++;
	}	
}

int	check_number(char *color, unsigned long long number, int index, char *save)
{
	if (number > INT_MAX || !(number <= 255))
	{
		ft_putstr_fd("Error\nRGB values must be between 0 and 255\n", 2);
		free(color);
		if (index > 0)
			free(save);
		return (1);
	}
	return (0);
}

int	take_color(char *color, int *i, int index, char *save)
{
	if (!color)
	{
		if (index > 0)
			free(save);
		return (1);
	}
	*i = 0;
	if (move_to_number(color, i))
	{
		free(color);
		if (index > 0)
			free(save);
		return (1);
	}
	return (0);
}
