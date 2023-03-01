/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgauvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 01:44:07 by dgauvin           #+#    #+#             */
/*   Updated: 2022/08/10 01:44:29 by dgauvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

unsigned long long	ft_atoull(const char *nptr)
{
	unsigned long long	sign;
	unsigned long long	result;
	unsigned long long	i;

	sign = 1;
	result = 0;
	i = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + nptr[i] - 48;
		i++;
	}
	return (sign * result);
}

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*pt;

	pt = (unsigned char *)s;
	while (n > 0)
	{
		pt[n - 1] = (unsigned char)c;
		n--;
	}
	return (s);
}	

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(src);
	if (size <= 0)
		return (len);
	while (i < size - 1 && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (len);
}	

char	*strtrim_end(char const *s1)
{
	char		*str;
	int			len;

	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	while (len > 0 && ft_isspace(s1[len - 1]) == 1)
		len--;
	if (len <= 0)
		return (ft_strdup(""));
	if (len == (int)ft_strlen(s1))
	{
		str = ft_strdup(s1);
		return (str);
	}
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, len + 1);
	return (str);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}	
