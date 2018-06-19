/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_normals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 13:00:07 by ldedier           #+#    #+#             */
/*   Updated: 2018/06/19 13:02:32 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec3 ft_normal_sphere(t_vec3 hit, t_object *object)
{
	return ft_vec3_normalized(res.intersection);
}

t_intersect ft_intersect_cone(t_ray ray, t_object *object)
{
	float       a;
	float       b;
	float       c;
	t_intersect res;
	
	res.color = object->color;
	float sangle;
	float cangle;

	cangle = pow(cos(object->object_union.cone.angle), 2);
	sangle = pow(sin(object->object_union.cone.angle), 2);

	a = cangle * ((ray.direction.z * ray.direction.z) + (ray.direction.y * ray.direction.y)) - sangle * (ray.direction.x  * ray.direction.x);
	b = 2 * (cangle * ((ray.position.z * ray.direction.z) + (ray.position.y * ray.direction.y)) - sangle * (ray.position.x * ray.direction.x));
	c = cangle * ((ray.position.z * ray.position.z) + (ray.position.y * ray.position.y)) -  sangle * (ray.position.x * ray.position.x);
	if ((b * b) - 4 * (a * c) < 0)
		res.t = -1;
	else
	{
		res.t = ft_min_pos((-b - sqrt((b * b) - (4.0 * a * c))) / (2.0 * a), (-b + sqrt((b * b) - (4.0 * a * c))) / (2.0 * a));
		res.intersection = ft_vec3_add(ft_vec3_scalar(ray.direction, res.t), ray.position);
		res.normal.x = sqrt(res.intersection.z * res.intersection.z + res.intersection.y * res.intersection.y) * tan(object->object_union.cone.angle);
		res.normal.y = res.intersection.y;
		res.normal.z = res.intersection.z;
	
		if (res.intersection.x > 0)
			res.normal.x *= -1;
	}
	return (res);
}

t_intersect ft_intersect_cylinder(t_ray ray, t_object *object)
{
	float       a;
	float       b;
	float       c;
	t_intersect res;

	res.color = object->color;
	a = (ray.direction.z * ray.direction.z) + (ray.direction.y * ray.direction.y);
	b = 2 * ((ray.position.z * ray.direction.z) + (ray.position.y * ray.direction.y));
	c = (ray.position.z * ray.position.z) + (ray.position.y * ray.position.y) - (object->object_union.cylinder.radius * object->object_union.cylinder.radius);

	if ((b * b) - 4 * (a * c) < 0)
		res.t = -1;
	else
	{
		res.t = ft_min_pos((-b - sqrt((b * b) - (4.0 * a * c))) / (2.0 * a), (-b + sqrt((b * b) - (4.0 * a * c))) / (2.0 * a));
		res.intersection = ft_vec3_add(ft_vec3_scalar(ray.direction, res.t), ray.position);
		res.normal = ft_new_vec3(0, res.intersection.y, res.intersection.z);
	}
	return (res);
}

t_intersect ft_intersect_plane(t_ray ray, t_object *object)
{
	t_intersect res;

	res.color = object->color;
	
	if (ray.direction.y == 0)
		res.t = -1;
	else
	{
		res.t = -ray.position.y / ray.direction.y;
		res.intersection = ft_vec3_add(ft_vec3_scalar(ray.direction, res.t), ray.position);
		res.normal = ft_new_vec3(0 , (ray.direction.y > 0 ? -1 : 1), 0);
	}
	return (res);
}
