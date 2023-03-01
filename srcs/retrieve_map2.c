/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retrieve_map2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgauvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 01:07:14 by dgauvin           #+#    #+#             */
/*   Updated: 2022/08/31 20:14:40 by dgauvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	check_map_validity(t_map map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map.lines_nbr)
	{
		j = 0;
		while (j < map.len_max - 1)
		{
			if (is_closed(map, i, j))
			{
				ft_putstr_fd("Error\nThe map must be closed\n", 2);
				return (1);
			}
			if (invalid_char_pos(map, i, j))
			{
				ft_putstr_fd("Error\nInvalid character position\n", 2);
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	fill_tmp_map(t_map **map, t_map_line **tmp, t_prep_tmp *prep_map)
{
	while ((*tmp)->line[prep_map->index2]
		&& prep_map->index2 < (*map)->len_max - 1)
	{
		if (invalid_el((*tmp)->line[prep_map->index2]))
		{
			prep_map->save = (*map)->lines_nbr;
			prep_map->index1++;
			ft_putstr_fd("Error\nThe map contains an invalid element\n", 2);
			return (1);
		}
		if (ft_isspace((*tmp)->line[prep_map->index2]))
			(*map)->tmp_map[prep_map->index1][prep_map->index2] = '-';
		else
			(*map)->tmp_map[prep_map->index1][prep_map->index2]
				= (*tmp)->line[prep_map->index2];
		prep_map->index2++;
	}
	while (prep_map->index2 < (*map)->len_max - 1)
	{
		(*map)->tmp_map[prep_map->index1][prep_map->index2] = '-';
		prep_map->index2++;
	}
	prep_map->index1++;
	return (0);
}

int	prepare_tmp_map(t_map *map, t_map_line **tmp)
{
	map->len_max = 0;
	map->lines_nbr = 0;
	*tmp = map->map_line;
	while ((*tmp)->line)
	{
		if (ft_strlen((*tmp)->line) > map->len_max)
			map->len_max = ft_strlen((*tmp)->line);
		*tmp = (*tmp)->next;
		map->lines_nbr++;
	}
	map->tmp_map = malloc(sizeof(char *) * (map->lines_nbr));
	if (!map->tmp_map)
		return (1);
	ft_memset(map->tmp_map, 0, map->lines_nbr);
	*tmp = map->map_line;
	return (0);
}

int	check_pursue_map_lines(char *line, t_map_line *map_line)
{
	if (!line)
	{
		map_line->pursue = 0;
		return (0);
	}
	map_line->empty = is_empty_line(line);
	if (map_line->empty)
	{
		if (!map_line->beg)
			return (0);
		else
			map_line->end = 1;
	}
	if (!map_line->empty)
	{
		if (!map_line->beg)
		{
			map_line->beg = 1;
			return (0);
		}
		if (map_line->end)
			return (1);
	}
	return (0);
}

int	get_final_map(t_cub *cub, t_map *map)
{
	if (check_map_validity(*map))
	{
		cub->retriever.save = NULL;
		free_tmp_map_line(*map);
		return (1);
	}
	if (convert_to_final_map(cub, map))
	{
		cub->retriever.save = NULL;
		free_tmp_map_line(*map);
		return (1);
	}
	free_tmp_map_line(*map);
	return (0);
}
