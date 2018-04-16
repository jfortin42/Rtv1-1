/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_3d_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherriau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 15:09:12 by aherriau          #+#    #+#             */
/*   Updated: 2018/04/16 15:48:10 by aherriau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmath.h"

t_v3d	ft_cross_product_v3d(t_v3d v1, t_v3d v2)
{
	t_v3d	v;

	v.x = (v1.y * v2.z) - (v1.z * v2.y);
	v.y = (v1.z * v2.x) - (v1.x * v2.z);
	v.z = (v1.x * v2.y) - (v1.y * v2.x);
	return (v);
}

t_v3d	ft_product_v3d(t_v3d v, float multiple)
{
	return (ft_new_v3d(v.x * multiple, v.y * multiple, v.z * multiple));
}

t_v3d	ft_scale_new_v3d(t_v3d v, float multiple)
{
	if (multiple)
		return (ft_new_v3d(v.x / multiple, v.y / multiple, v.z / multiple));
	return (v);
}

void	ft_scale_v3d(t_v3d *v, float multiple)
{
	if (multiple)
	{
		v->x /= multiple;
		v->y /= multiple;
		v->z /= multiple;
	}
}

t_v3d	ft_reverse_v3d(t_v3d v)
{
	return (ft_new_v3d(-v.x, -v.y, -v.z));
}
