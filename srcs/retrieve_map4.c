/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retrieve_map3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgauvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 01:10:11 by dgauvin           #+#    #+#             */
/*   Updated: 2022/08/31 20:11:16 by dgauvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	finalize_final_map(t_cub *cub, t_map *map)
{
	cub->lines_nbr = map->lines_nbr;
	cub->len_max = map->len_max;
	if (!cub->char_nbr)
	{
		ft_putstr_fd("Error\nThe map must contain a character position\n", 2);
		return (1);
	}
	return (0);
}

int	handle_char_pos(char el, int *char_pos, int *char_nbr)
{
	if (el == 'N')
			*char_pos = 3;
	if (el == 'S')
			*char_pos = 4;
	if (el == 'E')
			*char_pos = 5;
	if (el == 'W')
			*char_pos = 6;
	(*char_nbr)++;
	if ((*char_nbr) > 1)
		return (1);
	return (0);
}

int	fill_final_map(t_cub *cub, t_map *map, int start, int index)
{
	int	j;

	j = 0;
	while (j < map->len_max - 1)
	{
		if (map->tmp_map[index][j + start] == '-')
			cub->map[index][j] = 2;
		else if (map->tmp_map[index][j + start] == '1')
			cub->map[index][j] = 1;
		else if (map->tmp_map[index][j + start] == '0')
			cub->map[index][j] = 0;
		else
		{
			if (handle_char_pos(map->tmp_map[index][j + start],
				&cub->map[index][j], &cub->char_nbr))
			{
				ft_putstr_fd(SEVERAL_CHARACTER, 2);
				return (1);
			}
		}
		j++;
	}
	return (0);
}

int	convert_to_final_map(t_cub *cub, t_map *map)
{
	int	start;
	int	i;

	cub->map = malloc(sizeof(int *) * map->lines_nbr);
	if (!cub->map)
		return (1);
	determine_start(cub, map, &start, &i);
	while (++i < map->lines_nbr)
	{
		cub->map[i] = malloc(sizeof(int) * (map->len_max - 1));
		if (!cub->map[i] || fill_final_map(cub, map, start, i))
		{
			free(cub->map[i]);
			error_free_final_map(cub->map, i);
			return (1);
		}
	}
	if (finalize_final_map(cub, map))
	{
		error_free_final_map(cub->map, i);
		return (1);
	}
	return (0);
}
