/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgauvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 00:55:36 by dgauvin           #+#    #+#             */
/*   Updated: 2022/09/02 18:39:36 by dgauvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	free_tmp_save(t_map_line *tmp_save)
{
	int			i;
	t_map_line	*tmp;

	i = 0;
	tmp = tmp_save;
	while (tmp_save)
	{
		tmp = tmp_save;
		tmp_save = tmp_save->next;
		if (tmp->line)
			free(tmp->line);
		if (i > 0)
			free(tmp);
		i++;
	}
}

void	error_free_parse_cub(t_cub cub)
{
	free(cub.f_rgb);
	free(cub.c_rgb);
	if (cub.no_path)
		free(cub.no_path);
	if (cub.so_path)
		free(cub.so_path);
	if (cub.we_path)
		free(cub.we_path);
	if (cub.ea_path)
		free(cub.ea_path);
	if (cub.line_pointer)
		free(cub.line_pointer);
	if (cub.retriever.save)
		free(cub.retriever.save);
}

void	free_parsing(t_cub cub)
{
	int	i;

	i = 0;
	if (cub.no_path)
		free(cub.no_path);
	if (cub.so_path)
		free(cub.so_path);
	if (cub.we_path)
		free(cub.we_path);
	if (cub.ea_path)
		free(cub.ea_path);
	free(cub.f_rgb);
	free(cub.c_rgb);
	while (i < cub.lines_nbr)
	{
		free(cub.map[i]);
		i++;
	}
	free(cub.map);
}

void	free_tmp_map_line(t_map map)
{
	free_tmp_map(map);
	free_lines(map);
	free_map_line(map);
}
