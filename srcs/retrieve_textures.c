/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retrieve_textures.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgauvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 01:38:19 by dgauvin           #+#    #+#             */
/*   Updated: 2022/08/10 01:41:56 by dgauvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	is_empty_line(char *line)
{
	int	i;

	if (!line)
		return (1);
	i = 0;
	while (line[i])
	{
		if (!ft_isspace(line[i]))
			return (0);
		i++;
	}
	if (i == ft_strlen(line))
		return (1);
	return (0);
}

int	check_pursue_texture(t_cub *cub, int *pursue, char *line)
{
	if (cub->no_count > 1 || cub->so_count > 1
		|| cub->we_count > 1 || cub->ea_count > 1)
	{
		ft_putstr_fd("Error\nYou entered a wrong texture element\n", 2);
		return (1);
	}
	if (cub->no_count == 1 && cub->so_count == 1
		&& cub->we_count == 1 && cub->ea_count == 1)
		*pursue = 0;
	if (!line)
		return (1);
	return (0);
}

int	get_texture(t_cub *cub, char *line)
{
	char	*path;

	if (cub->empty_line)
		return (0);
	if (is_empty_line(line))
		return (1);
	path = ft_strtrim(line);
	if (!path)
		return (1);
	if (!ft_strlen(line))
		return (0);
	if (take_texture(cub, path))
	{
		free(path);
		ft_putstr_fd("Error\nYou entered a wrong texture element\n", 2);
		return (1);
	}
	free(path);
	return (0);
}

int	get_direction(t_cub *cub, char **line)
{
	int	i;

	i = 0;
	if (is_empty_line(*line))
	{
		cub->empty_line = 1;
		return (0);
	}
	while ((*line)[i] && ft_isspace((*line)[i]))
		i++;
	if (is_direction(cub, *line + i))
		return (1);
	if (ft_strlen(*line) > i + 3)
		*line += i + 3;
	return (0);
}

int	retrieve_textures(t_cub *cub)
{
	cub->retriever.pursue = 1;
	while (cub->retriever.pursue)
	{
		cub->empty_line = 0;
		cub->retriever.line = get_next_line(cub->fd, &cub->line_pointer);
		if (!cub->retriever.line)
			return (1);
		cub->retriever.save = cub->retriever.line;
		if (get_direction(cub, &cub->retriever.line))
			return (1);
		if (get_texture(cub, cub->retriever.line))
			return (1);
		if (check_pursue_texture(cub, &cub->retriever.pursue,
				cub->retriever.line))
			return (1);
		free(cub->retriever.save);
		cub->retriever.save = NULL;
	}
	if (check_texture_path(cub->no_path, cub->so_path,
			cub->ea_path, cub->we_path))
	{
		ft_putstr_fd("Error\nYou entered a wrong texture path\n", 2);
		return (1);
	}
	return (0);
}
