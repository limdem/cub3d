/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgauvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 18:49:36 by dgauvin           #+#    #+#             */
/*   Updated: 2022/01/06 16:33:40 by dgauvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}	

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

int	is_current_line(char *str, int reader)
{
	int	i;

	i = 0;
	if (reader == 0)
		return (1);
	if (!str)
		return (1);
	while (str[i])
	{
		if (str[i] == '\n')
			return (0);
		i++;
	}
	return (1);
}

void	*ft_memmove(void *dest, const void *src, int n)
{
	unsigned char		*pt_dest;
	const unsigned char	*pt_src;

	pt_dest = (unsigned char *)dest;
	pt_src = (const unsigned char *)src;
	if (!dest && !src)
		return (NULL);
	if (pt_src < pt_dest)
	{
		while (n--)
			*(pt_dest + n) = *(pt_src + n);
	}
	else
	{
		while (n--)
			*pt_dest++ = *pt_src++;
	}
	return (dest);
}
