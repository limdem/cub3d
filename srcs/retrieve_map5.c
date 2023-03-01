/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retrieve_map4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgauvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 01:13:42 by dgauvin           #+#    #+#             */
/*   Updated: 2022/08/31 20:10:25 by dgauvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	determine_start(t_cub *cub, t_map *map, int *start, int *index)
{
	int	i;
	int	j;

	i = 0;
	*start = map->len_max;
	while (i < map->lines_nbr)
	{
		j = 0;
		while (j < map->len_max - 1)
		{
			if (map->tmp_map[i][j] != '-' && j < *start)
				*start = j;
			j++;
		}
		i++;
	}
	cub->char_nbr = 0;
	map->len_max -= *start;
	*index = -1;
}

int	invalid_el(char el)
{
	if (ft_isspace(el))
		return (0);
	if (!(el == '1' || el == '0' || el == 'N'
			|| el == 'S' || el == 'E' || el == 'W'))
		return (1);
	return (0);
}

int	is_closed(t_map map, int index1, int index2)
{
	if (map.tmp_map[index1][index2] == '0')
	{
		if (index1 == 0 || index1 == map.lines_nbr - 1)
			return (1);
		if (index2 == 0 || index2 == map.len_max - 2)
			return (1);
		if (map.tmp_map[index1][index2 - 1] == '-'
			|| map.tmp_map[index1][index2 + 1] == '-')
			return (1);
		if ((map.tmp_map[index1 - 1][index2] == '-'
			|| map.tmp_map[index1 + 1][index2] == '-'))
			return (1);
	}
	return (0);
}
