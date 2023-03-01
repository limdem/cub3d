/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retrieve_map3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgauvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 01:07:14 by dgauvin           #+#    #+#             */
/*   Updated: 2022/09/02 18:30:16 by dgauvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	invalid_char_pos(t_map map, int index1, int index2)
{
	int	character;

	character = 0;
	if (map.tmp_map[index1][index2] == 'N' || map.tmp_map[index1][index2] == 'S'
			|| map.tmp_map[index1][index2] == 'W'
			|| map.tmp_map[index1][index2] == 'E')
		character = 1;
	if (!character)
		return (0);
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
	return (0);
}
