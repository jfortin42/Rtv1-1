/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherriau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 13:16:32 by aherriau          #+#    #+#             */
/*   Updated: 2018/06/20 21:54:50 by aherriau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

float	ft_min_pos(float t1, float t2)
{
	if ((t1 < t2 || t2 < 0) && t1 > 0)
		return (t1);
	if ((t2 < t1 || t1 < 0) && t2 > 0)
		return (t2);
	else
		return (-1);
}

int		ft_get_color_reduction(int color, float reduc)
{
	int		r;
	int		g;
	int		b;

	r = (color >> 16) & (0xff);
	g = (color >> 8) & (0xff);
	b = color & (0xff);
	r = ft_clamp(0, r * reduc, 255);
	g = ft_clamp(0, g * reduc, 255);
	b = ft_clamp(0, b * reduc, 255);
	return ((r << 16) | (g << 8) | b);
}

int		ft_color_add(int color, float to_add)
{
	int		r;
	int		g;
	int		b;

	r = (color >> 16) & (0xff);
	g = (color >> 8) & (0xff);
	b = color & (0xff);
	r = ft_clamp(0, r + (255 * to_add), 255);
	g = ft_clamp(0, g + (255 * to_add), 255);
	b = ft_clamp(0, b + (255 * to_add), 255);
	return ((r << 16) | (g << 8) | b);
}
