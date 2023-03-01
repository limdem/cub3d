/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgauvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 00:56:09 by dgauvin           #+#    #+#             */
/*   Updated: 2022/08/10 00:57:34 by dgauvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	error_free_final_map(int **map, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	free_map_line(t_map map)
{
	t_map_line	*map_line;
	int			i;
	int			j;

	i = 0;
	map_line = map.map_line;
	while (i < map.lines_nbr)
	{
		j = i;
		while (j < map.lines_nbr)
		{
			map.map_line = map.map_line->next;
			j++;
		}
		free(map.map_line);
		i++;
		map.map_line = map_line;
	}
}

void	free_lines(t_map map)
{
	char	*save;
	int		i;

	i = 0;
	while (i < map.lines_nbr)
	{
		save = map.map_line->line;
		if (map.lines_nbr > 1)
		map.map_line = map.map_line->next;
		free(save);
		i++;
	}
}

void	free_tmp_map_line1(t_map map, char *line, char *line_pointer)
{
	free(line);
	free(line_pointer);
	free_lines(map);
	free_map_line(map);
}

void	free_tmp_map(t_map map)
{
	int	i;

	i = 0;
	while (i < map.lines_nbr)
	{
		if (map.tmp_map[i])
			free(map.tmp_map[i]);
		i++;
	}
	free(map.tmp_map);
}
