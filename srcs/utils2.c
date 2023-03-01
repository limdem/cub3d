/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgauvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 01:42:20 by dgauvin           #+#    #+#             */
/*   Updated: 2022/08/10 01:43:53 by dgauvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*new_subs;
	size_t		i;

	if (!s)
		return (NULL);
	if (start > (long unsigned int)ft_strlen(s))
		return (ft_strdup(""));
	if (len > (long unsigned int)ft_strlen(s))
		new_subs = malloc(ft_strlen(s) * sizeof(char) + 1);
	else if (len == (long unsigned int)ft_strlen(s))
		new_subs = malloc((len - ft_strlen(s) + 1) * sizeof(char) + 1);
	else
		new_subs = malloc(len * sizeof(char) + 1);
	if (!new_subs)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		new_subs[i] = s[start + i];
		i++;
	}
	new_subs[i] = '\0';
	return (new_subs);
}

char	*ft_strdup(const char *s)
{
	char	*new_s;
	int		i;

	new_s = malloc(ft_strlen(s) * sizeof(char) + 1);
	if (!new_s)
		return (NULL);
	i = 0;
	while (s[i])
	{
		new_s[i] = s[i];
		i++;
	}
	new_s[i] = '\0';
	return (new_s);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		if (s1[i] == '\0' || s2[i] == '\0')
			return (0);
		i++;
	}	
	return (0);
}

int	ft_isspace(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}	

char	*ft_strtrim(char const *s1)
{
	char		*str;
	int			i;
	int			len;

	i = 0;
	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	while (s1[i] && ft_isspace(s1[i]) == 1)
		i++;
	while (len > 0 && ft_isspace(s1[len - 1]) == 1)
		len--;
	if (len - i <= 0)
		return (ft_strdup(""));
	if (i == 0 && len == (int)ft_strlen(s1))
	{
		str = ft_strdup(s1);
		return (str);
	}		
	str = ft_substr(s1, i, len - i);
	return (str);
}
