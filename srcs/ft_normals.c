/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_normals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 16:05:39 by ldedier           #+#    #+#             */
/*   Updated: 2018/06/19 16:42:14 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec3		ft_normal_sphere(t_vec3 point, t_object *object)
{
	(void)object;
	return (normalize(point));
}

t_vec3		ft_normal_cone(t_vec3 intersection, t_object *object)
{
	t_vec3 res;

	res.x = sqrt(intersection.z * intersection.z +
				intersection.y * intersection.y) *
					tan(object->object_union.cone.angle);
	res.y = intersection.y;
	res.z = intersection.z;
	if (intersection.x > 0)
		res.x *= -1;
	return (normalize(res));
}

t_vec3		ft_normal_cylinder(t_vec3 intersection, t_object *object)
{
	(void)object;
	return (normalize(ft_new_vec3(0, intersection.y, intersection.z)));
}

t_vec3		ft_normal_plane(t_vec3 point, t_object *object)
{
	(void)point;
	(void)object;
	return (ft_new_vec3(0, 1, 0));
}
