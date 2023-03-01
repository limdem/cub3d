/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlanani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 20:15:29 by rlanani           #+#    #+#             */
/*   Updated: 2022/09/02 18:29:43 by dgauvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/cub3d.h"

int	initialize_main_parsing(t_cub *cub, int argc, char **argv)
{
	if (handle_parsing(cub, argc, argv))
	{
		error_free_parse_cub(*cub);
		return (0);
	}
	return (1);
}

void	show_cub(t_cub cub)
{
	int	i;
	int	j;

	printf("cub.no_path: %s\n", cub.no_path);
	printf("cub.so_path: %s\n", cub.so_path);
	printf("cub.we_path: %s\n", cub.we_path);
	printf("cub.ea_path: %s\n", cub.ea_path);
	printf("cub.f_rgb[0]: %d\n", cub.f_rgb[0]);
	printf("cub.f_rgb[1]: %d\n", cub.f_rgb[1]);
	printf("cub.f_rgb[2]: %d\n", cub.f_rgb[2]);
	printf("cub.c_rgb[0]: %d\n", cub.c_rgb[0]);
	printf("cub.c_rgb[1]: %d\n", cub.c_rgb[1]);
	printf("cub.c_rgb[2]: %d\n", cub.c_rgb[2]);
	i = 0;
	while (i < cub.lines_nbr)
	{
		j = 0;
		while (j < cub.len_max - 1)
		{
			printf("%d", cub.map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_data	img;
	t_data	*texture;
	t_ray	raycast;
	t_cub	cub;

	if (!initialize_main_parsing(&cub, argc, argv))
		return (1);
	initialize_raycast(&raycast, &cub);
	texture = malloc(sizeof(t_data) * 5);
	if (!texture)
	{
		free_parsing(cub);
		return (1);
	}
	if (!initialise_img(&raycast, &img, texture, &cub)
		|| !initialize_texture(texture, img.mlx, cub)
		|| !initialize_data(&img, texture))
	{
		free_parsing(cub);
		free(texture);
		return (1);
	}
	initialise_raycasting(&raycast, &img);
	return (0);
}
