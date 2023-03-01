/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgauvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 00:58:12 by dgauvin           #+#    #+#             */
/*   Updated: 2022/08/10 01:01:03 by dgauvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	initialize_parsing(t_cub *cub)
{
	cub->empty_line = 0;
	cub->no_count = 0;
	cub->so_count = 0;
	cub->we_count = 0;
	cub->ea_count = 0;
	cub->f_count = 0;
	cub->c_count = 0;
	cub->no_path = NULL;
	cub->so_path = NULL;
	cub->we_path = NULL;
	cub->ea_path = NULL;
	cub->line_pointer = NULL;
	cub->retriever.save = NULL;
	cub->f_rgb = malloc(sizeof(int) * 3);
	if (!cub->f_rgb)
		return (1);
	cub->c_rgb = malloc(sizeof(int) * 3);
	if (!cub->c_rgb)
		return (1);
	return (0);
}

int	is_empty_column(t_map map, int column)
{
	int	empty;
	int	i;

	i = 0;
	empty = 1;
	while (i < map.lines_nbr)
	{
		if (map.tmp_map[i][column] != '-')
			empty = 0;
		i++;
	}
	return (empty);
}

int	parse_cub(t_cub *cub, int argc, char *argv[])
{
	if (initialize_parsing(cub))
		return (1);
	if (open_scene_file(&cub->fd, argc, argv) == 1)
		return (1);
	if (retrieve_textures(cub))
		return (2);
	if (retrieve_floor_ceiling(cub))
		return (2);
	if (retrieve_map(cub))
		return (2);
	return (0);
}

int	handle_parsing(t_cub *cub, int argc, char *argv[])
{
	int	result;

	result = parse_cub(cub, argc, argv);
	if (result)
	{
		if (result == 2)
			close(cub->fd);
		return (1);
	}
	close(cub->fd);
	return (0);
}
