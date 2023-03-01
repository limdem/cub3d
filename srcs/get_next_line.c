/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgauvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 18:49:36 by dgauvin           #+#    #+#             */
/*   Updated: 2022/01/07 02:50:21 by dgauvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

char	*custom_join(char *dest, char *src)
{
	char	*mod_line;

	if (!dest && !src)
		return (NULL);
	mod_line = malloc((ft_strlen(src) + ft_strlen(dest) + 1) * sizeof(char));
	if (!mod_line)
		return (NULL);
	ft_memmove(mod_line, dest, ft_strlen(dest));
	ft_memmove(mod_line + ft_strlen(dest), src, ft_strlen(src));
	mod_line[ft_strlen(dest) + ft_strlen(src)] = '\0';
	if (dest)
		free(dest);
	return (mod_line);
}	

char	*get_line(char *str)
{
	int		i;
	char	*r_line;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	if (i == 0 && str[i] != '\n')
		return (NULL);
	r_line = malloc((i + 2) * sizeof(char));
	if (!r_line)
		return (NULL);
	ft_memmove(r_line, str, i + 1);
	r_line[i + 1] = '\0';
	return (r_line);
}

char	*save_next_line(char *str)
{
	char	*next_line;
	int		i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	next_line = malloc((ft_strlen(str) - i + 1) * sizeof(char));
	if (!next_line)
		return (NULL);
	if (str[i] == '\n')
	{
		ft_memmove(next_line, str + i + 1, ft_strlen(str) - i - 1);
		next_line[ft_strlen(str) - i - 1] = 0;
	}
	else if (str[i] != '\n' || !ft_strlen(next_line))
	{
		free(str);
		free(next_line);
		return (NULL);
	}	
	free(str);
	return (next_line);
}

char	*get_next_line(int fd, char **line_pointer)
{
	static char	*line_saver;
	char		*r_line;
	char		*buffer;
	int			reader;

	reader = 1;
	while (is_current_line(line_saver, reader) && reader > 0)
	{
		buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!buffer)
			return (NULL);
		reader = read(fd, buffer, BUFFER_SIZE);
		if (reader == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[reader] = '\0';
		line_saver = custom_join(line_saver, buffer);
		free(buffer);
	}
	r_line = get_line(line_saver);
	line_saver = save_next_line(line_saver);
	*line_pointer = line_saver;
	return (r_line);
}
