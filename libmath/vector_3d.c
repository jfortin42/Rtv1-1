/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherriau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 14:25:34 by aherriau          #+#    #+#             */
/*   Updated: 2018/04/16 15:21:09 by aherriau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmath.h"

t_v3d	ft_new_zero_v3d(void)
{
	t_v3d	v;

	v.x = 0.0f;
	v.y = 0.0f;
	v.z = 0.0f;
	return (v);
}

t_v3d	ft_new_v3d(float x, float y, float z)
{
	t_v3d	v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

t_v3d	ft_plus_new_v3d(t_v3d v1, t_v3d v2)
{
	return (ft_new_v3d(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z));
}

void	ft_plus_v3d(t_v3d *v1, t_v3d v2)
{
	v1->x += v2.x;
	v1->y += v2.y;
	v1->z += v2.z;
}

t_v3d	ft_minus_new_v3d(t_v3d v1, t_v3d v2)
{
	return (ft_new_v3d(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z));
}
