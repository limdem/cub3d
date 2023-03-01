/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgauvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 00:47:36 by dgauvin           #+#    #+#             */
/*   Updated: 2022/08/10 00:55:11 by dgauvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	check_is_directory(char *path)
{
	int	fd;

	fd = open(path, __O_DIRECTORY, 0777);
	if (fd != -1)
	{
		close(fd);
		ft_putstr_fd(INVALID_FILE, 2);
		return (1);
	}
	return (0);
}

int	check_scene_file(char *path)
{
	int	len;

	if (check_is_directory(path))
		return (1);
	len = ft_strlen(path);
	if (ft_strncmp(path + len - 4, ".cub", 4))
	{
		ft_putstr_fd("Error\nWrong file type\n", 2);
		return (1);
	}
	while (len - 4 > 0 && path[len - 5] != '/')
	{
		if (path[len - 5] == '.')
		{
			ft_putstr_fd("Error\nWrong file type\n", 2);
			return (1);
		}
		len--;
	}
	return (0);
}

int	open_scene_file(int *fd, int argc, char *argv[])
{
	if (argc != 2)
	{
		ft_putstr_fd(INVALID_FILE, 2);
		return (1);
	}
	if (check_scene_file(argv[1]))
		return (1);
	*fd = open(argv[1], O_RDONLY, 0777);
	if (*fd == -1)
	{
		ft_putstr_fd("Error\nCould not open the scene file\n", 2);
		return (1);
	}
	return (0);
}
