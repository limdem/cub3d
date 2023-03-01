/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retrieve_textures2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgauvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 01:36:04 by dgauvin           #+#    #+#             */
/*   Updated: 2022/08/10 01:38:01 by dgauvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	check_texture_path(char *no_path, char *so_path,
		char *ea_path, char *we_path)
{
	int	fd;

	if (!no_path || ! so_path || ! ea_path || ! we_path)
		return (1);
	fd = open(no_path, O_RDONLY, 0777);
	if (fd == -1)
		return (1);
	close(fd);
	fd = open(so_path, O_RDONLY, 0777);
	if (fd == -1)
		return (1);
	close(fd);
	fd = open(ea_path, O_RDONLY, 0777);
	if (fd == -1)
		return (1);
	close(fd);
	fd = open(we_path, O_RDONLY, 0777);
	if (fd == -1)
		return (1);
	close(fd);
	return (0);
}

void	get_texture_file(t_cub *cub, char *path)
{
	if (cub->direction == 1)
	{
		cub->no_count++;
		if (cub->no_count == 1)
			cub->no_path = ft_strdup(path);
	}
	if (cub->direction == 2)
	{
		cub->so_count++;
		if (cub->so_count == 1)
			cub->so_path = ft_strdup(path);
	}
	if (cub->direction == 3)
	{
		cub->we_count++;
		if (cub->we_count == 1)
			cub->we_path = ft_strdup(path);
	}
	if (cub->direction == 4)
	{
		cub->ea_count++;
		if (cub->ea_count == 1)
			cub->ea_path = ft_strdup(path);
	}
}

int	take_texture(t_cub *cub, char *path)
{
	int	j;

	j = 0;
	while (path[j])
	{
		if (ft_isspace(path[j]) && path[j] != 10)
			return (1);
		j++;
	}
	get_texture_file(cub, path);
	return (0);
}

int	is_direction(t_cub *cub, char *line)
{
	cub->direction = 0;
	if (!ft_isspace(line[2]))
	{
		ft_putstr_fd("Error\nYou entered a wrong texture element\n", 2);
		return (1);
	}
	if (!ft_strncmp(line, "NO", 2))
		cub->direction = 1;
	if (!ft_strncmp(line, "SO", 2))
		cub->direction = 2;
	if (!ft_strncmp(line, "WE", 2))
		cub->direction = 3;
	if (!ft_strncmp(line, "EA", 2))
		cub->direction = 4;
	if (!cub->direction)
	{
		ft_putstr_fd("Error\nYou entered a wrong texture element\n", 2);
		return (1);
	}
	return (0);
}
