/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orientation_player.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlanani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 12:13:39 by rlanani           #+#    #+#             */
/*   Updated: 2022/08/27 13:18:51 by rlanani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	east(t_ray *raycast)
{
	double	oldplanex;
	double	olddirx;

	olddirx = raycast->dirx;
	oldplanex = raycast->planx;
	raycast->dirx = raycast->dirx * cos(-5.20 * 1.8 / 2)
		- raycast->diry * sin(-5.20 * 1.8 / 2);
	raycast->diry = olddirx * sin(-5.20 * 1.8 / 2)
		+ raycast->diry * cos(-5.20 * 1.8 / 2);
	raycast->planx = raycast->planx * cos(-5.20 * 1.8 / 2)
		- raycast->plany * sin(-5.20 * 1.8 / 2);
	raycast->plany = oldplanex * sin(-5.20 * 1.8 / 2)
		+ raycast->plany * cos(-5.20 * 1.8 / 2);
	return (0);
}

int	north(t_ray *raycast)
{
	double	oldplanex;
	double	olddirx;

	olddirx = raycast->dirx;
	oldplanex = raycast->planx;
	raycast->dirx = raycast->dirx * cos(-3.50 * 1.8 / 2)
		- raycast->diry * sin(-3.50 * 1.8 / 2);
	raycast->diry = olddirx * sin(-3.50 * 1.8 / 2)
		+ raycast->diry * cos(-3.50 * 1.8 / 2);
	raycast->planx = raycast->planx * cos(-3.50 * 1.8 / 2)
		- raycast->plany * sin(-3.50 * 1.8 / 2);
	raycast->plany = oldplanex * sin(-3.50 * 1.8 / 2)
		+ raycast->plany * cos(-3.50 * 1.8 / 2);
	return (0);
}

int	south(t_ray *raycast)
{
	double	oldplanex;
	double	olddirx;

	olddirx = raycast->dirx;
	oldplanex = raycast->planx;
	raycast->dirx = raycast->dirx * cos(-1.66 * 1.8 / 2)
		- raycast->diry * sin(-1.66 * 1.8 / 2);
	raycast->diry = olddirx * sin(-1.66 * 1.8 / 2)
		+ raycast->diry * cos(-1.66 * 1.8 / 2);
	raycast->planx = raycast->planx * cos(-1.66 * 1.8 / 2)
		- raycast->plany * sin(-1.66 * 1.8 / 2);
	raycast->plany = oldplanex * sin(-1.66 * 1.8 / 2)
		+ raycast->plany * cos(-1.66 * 1.8 / 2);
	return (0);
}
