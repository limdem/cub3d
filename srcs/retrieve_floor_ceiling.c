/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retrieve_floor_ceiling.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgauvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 01:05:02 by dgauvin           #+#    #+#             */
/*   Updated: 2022/08/10 01:06:47 by dgauvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	check_pursue_floor_ceiling(t_cub *cub, int *pursue)
{
	if (cub->f_count > 3 || cub->c_count > 3)
		return (1);
	if (cub->f_count == 3 && cub->c_count == 3)
		*pursue = 0;
	return (0);
}

int	get_color(t_cub *cub, char *line)
{
	int		result;
	char	*tmp;
	char	*save;

	save = 0;
	if (cub->empty_line)
		return (0);
	tmp = ft_strdup(line);
	if (!tmp)
		return (1);
	result = handle_get_number(cub, tmp, save);
	if (result > 0)
	{
		if (result == 1)
			free(tmp);
		return (1);
	}
	return (0);
}

int	get_floor_ceiling(t_cub *cub, char **line)
{
	int		i;

	i = 0;
	if (is_empty_line(*line))
	{
		cub->empty_line = 1;
		return (0);
	}
	while ((*line)[i] && ft_isspace((*line)[i]))
		i++;
	if (is_floor_ceiling(cub, *line + i))
		return (1);
	if (ft_strlen(*line) > i + 2)
		*line += i + 2;
	return (0);
}

int	retrieve_floor_ceiling(t_cub *cub)
{
	cub->retriever.pursue = 1;
	while (cub->retriever.pursue)
	{
		cub->empty_line = 0;
		cub->retriever.line = get_next_line(cub->fd, &cub->line_pointer);
		if (!cub->retriever.line)
			return (1);
		cub->retriever.save = cub->retriever.line;
		if (get_floor_ceiling(cub, &cub->retriever.line))
			return (1);
		if (get_color(cub, cub->retriever.line))
			return (1);
		if (check_pursue_floor_ceiling(cub, &cub->retriever.pursue))
			return (1);
		free(cub->retriever.save);
		cub->retriever.save = NULL;
	}
	return (0);
}
