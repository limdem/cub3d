/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retrieve_floor_ceiling2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgauvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 01:01:31 by dgauvin           #+#    #+#             */
/*   Updated: 2022/08/10 01:03:39 by dgauvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	go_to_next_number_index2(char **line, char **save)
{
	int	i;

	i = 0;
	*save = *line;
	while ((*line)[i])
	{
		if (!ft_isspace((*line)[i]))
			return (1);
		i++;
	}
	return (0);
}

int	go_to_next_number(char **line, char **save)
{
	int	i;

	i = 0;
	*save = *line;
	if ((*line)[i] == ',')
		*line += 1;
	else
	{
		while ((*line)[i] != ',')
		{
			if (!ft_isspace((*line)[i]))
				return (1);
			i++;
		}
		*line += i + 1;
	}
	return (0);
}

int	get_number(t_cub *cub, char **line, int index, char *save)
{
	unsigned long long	number;
	int					i;
	char				*color;

	i = 0;
	color = ft_strtrim(*line);
	if (take_color(color, &i, index, save))
		return (1);
	number = ft_atoull(color);
	if (check_number(color, number, index, save))
		return (1);
	take_number(cub, number, index);
	if (index == 0)
		free(*line);
	else
		free(save);
	*line = ft_strdup(color + i);
	free(color);
	return (0);
}

int	handle_get_number(t_cub *cub, char *tmp, char *save)
{
	if (get_number(cub, &tmp, 0, save))
		return (1);
	if (go_to_next_number(&tmp, &save))
	{
		free(tmp);
		return (2);
	}
	if (get_number(cub, &tmp, 1, save))
		return (2);
	if (go_to_next_number(&tmp, &save))
	{
		free(tmp);
		return (4);
	}
	if (get_number(cub, &tmp, 2, save))
		return (2);
	if (go_to_next_number_index2(&tmp, &save))
	{
		free(save);
		return (6);
	}
	free(tmp);
	return (0);
}

int	is_floor_ceiling(t_cub *cub, char *line)
{
	cub->floor_ceiling = 0;
	if (!line[0])
		return (0);
	if (!ft_isspace(line[1]))
	{
		ft_putstr_fd("Error\nYou entered a wrong color element\n", 2);
		return (1);
	}
	if (!ft_strncmp(line, "F", 1))
		cub->floor_ceiling = 1;
	if (!ft_strncmp(line, "C", 1))
		cub->floor_ceiling = 2;
	if (!cub->floor_ceiling)
	{
		ft_putstr_fd("Error\nYou entered a wrong color element\n", 2);
		return (1);
	}
	return (0);
}
