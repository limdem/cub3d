/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retrieve_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgauvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 01:15:04 by dgauvin           #+#    #+#             */
/*   Updated: 2022/09/02 18:40:09 by dgauvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	create_tmp_map(t_map *map)
{
	t_map_line	*tmp;
	t_prep_tmp	prep_map;

	if (prepare_tmp_map(map, &tmp))
		return (1);
	prep_map.index1 = 0;
	while (tmp->line)
	{
		prep_map.index2 = 0;
		map->tmp_map[prep_map.index1]
			= malloc(sizeof(char) * (map->len_max - 1));
		if (!map->tmp_map[prep_map.index1]
			|| fill_tmp_map(&map, &tmp, &prep_map))
		{
			map->lines_nbr = prep_map.index1;
			free_tmp_map(*map);
			map->lines_nbr = prep_map.save;
			return (1);
		}
		if (tmp->next->line)
			tmp = tmp->next;
		else
			break ;
	}
	return (0);
}

int	create_map_line(t_map map, t_map_line map_line,
	t_map_line **tmp, char *tmp_line)
{
	(*tmp)->line = tmp_line;
	if (map_line.pursue)
	{
		if (!is_empty_line(tmp_line))
		{
			map.lines_nbr++;
			(*tmp)->next = malloc(sizeof(t_map_line));
			if (!(*tmp)->next)
				return (1);
			*tmp = (*tmp)->next;
			(*tmp)->line = NULL;
		}
		else
		{
			free((*tmp)->line);
			(*tmp)->line = NULL;
			(*tmp)->next = NULL;
		}
	}
	(*tmp)->next = NULL;
	return (0);
}

int	check_map_lines(t_map map, char *tmp_line,
	t_map_line *map_line, t_map_line *tmp_save)
{
	if (check_pursue_map_lines(tmp_line, map_line))
	{
		free_tmp_save(tmp_save);
		free_lines(map);
		free_map_line(map);
		return (1);
	}
	return (0);
}

void	prepare_map(t_map *map, t_map_line *map_line,
	t_map_line **tmp, char **tmp_line)
{
	map_line->pursue = 1;
	map_line->beg = 0;
	map_line->end = 0;
	*tmp = map_line;
	*tmp_line = NULL;
	map->map_line = map_line;
	map->lines_nbr = 0;
}

int	retrieve_map(t_cub *cub)
{
	t_map_ret	map_ret;

	prepare_map(&map_ret.map, &map_ret.map_line,
		&map_ret.tmp, &cub->retriever.line);
	map_ret.tmp_save = map_ret.tmp;
	while (map_ret.map_line.pursue)
	{
		cub->retriever.line = get_next_line(cub->fd, &cub->line_pointer);
		cub->retriever.save = cub->retriever.line;
		if (check_map_lines(map_ret.map, cub->retriever.line,
				&map_ret.map_line, map_ret.tmp_save))
			return (1);
		if (create_map_line(map_ret.map, map_ret.map_line,
				&map_ret.tmp, cub->retriever.line))
			return (1);
	}
	if (create_tmp_map(&map_ret.map))
	{
		free_tmp_map_line1(map_ret.map, cub->retriever.line, cub->line_pointer);
		return (1);
	}
	if (get_final_map(cub, &map_ret.map))
		return (1);
	return (0);
}
