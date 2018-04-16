/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_3d_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherriau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 15:48:40 by aherriau          #+#    #+#             */
/*   Updated: 2018/04/16 15:59:10 by aherriau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmath.h"

float	ft_dot_product_v3d(t_v3d v1, t_v3d v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

float	ft_magnitude_v3d(t_v3d v)
{
	return ((float)sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

void	ft_normalize_v3d(t_v3d *v)
{
	float	mag;

	mag = ft_magnitude_v3d(*v);
	if (mag)
	{
		v->x /= mag;
		v->y /= mag;
		v->z /= mag;
	}
}

float	ft_square_length_v3d(t_v3d v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}

t_v3d	ft_reflect_v3d(t_v3d v, t_v3d n)
{
	float	fac;

	fac = 2.0f * (n.x * v.x + n.y * v.y + n.z * v.z);
	return (ft_new_v3d(fac * n.x - v.x, fac * n.y - v.y, fac * n.z - v.z));
}
