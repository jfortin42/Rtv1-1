/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intersections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 16:01:10 by ldedier           #+#    #+#             */
/*   Updated: 2018/06/20 22:17:38 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

float			ft_intersect_sphere(t_ray ray, t_object *object)
{
	float		a;
	float		b;
	float		c;
	float		t;

	a = (ray.direction.x * ray.direction.x) +
		(ray.direction.y * ray.direction.y) +
		(ray.direction.z * ray.direction.z);
	b = 2 * ((ray.position.x * ray.direction.x) + (ray.position.y *
				ray.direction.y) + (ray.position.z * ray.direction.z));
	c = (ray.position.x * ray.position.x) + (ray.position.y * ray.position.y) +
		(ray.position.z * ray.position.z) -
		(object->object_union.sphere.radius *
			object->object_union.sphere.radius);
	if ((b * b) - 4 * (a * c) < 0)
		t = -1;
	else
		t = ft_min_pos((-b - sqrt((b * b) - (4.0 * a * c))) / (2.0 * a),
				(-b + sqrt((b * b) - (4.0 * a * c))) / (2.0 * a));
	return (t);
}

float			ft_intersect_cone(t_ray ray, t_object *object)
{
	float		a;
	float		b;
	float		c;
	float		t;
	t_auxcone	xo;

	xo.cangle = pow(cos(object->object_union.cone.angle), 2);
	xo.sangle = pow(sin(object->object_union.cone.angle), 2);
	a = xo.cangle * ((ray.direction.z * ray.direction.z) + (ray.direction.y *
		ray.direction.y)) - xo.sangle * (ray.direction.x * ray.direction.x);
	b = 2 * (xo.cangle * ((ray.position.z * ray.direction.z) + (ray.position.y *
			ray.direction.y)) - xo.sangle * (ray.position.x * ray.direction.x));
	c = xo.cangle * ((ray.position.z * ray.position.z) + (ray.position.y *
				ray.position.y)) - xo.sangle *
		(ray.position.x * ray.position.x);
	if ((b * b) - 4 * (a * c) < 0)
		t = -1;
	else
		t = ft_min_pos((-b - sqrt((b * b) - (4.0 * a * c))) / (2.0 * a),
				(-b + sqrt((b * b) - (4.0 * a * c))) / (2.0 * a));
	return (t);
}

float			ft_intersect_cylinder(t_ray ray, t_object *object)
{
	float		a;
	float		b;
	float		c;
	float		t;

	a = (ray.direction.z * ray.direction.z) +
		(ray.direction.y * ray.direction.y);
	b = 2 * ((ray.position.z * ray.direction.z) +
			(ray.position.y * ray.direction.y));
	c = (ray.position.z * ray.position.z) + (ray.position.y * ray.position.y) -
		(object->object_union.cylinder.radius *
			object->object_union.cylinder.radius);
	if ((b * b) - 4 * (a * c) < 0)
		t = -1;
	else
		t = ft_min_pos((-b - sqrt((b * b) - (4.0 * a * c))) / (2.0 * a),
				(-b + sqrt((b * b) - (4.0 * a * c))) / (2.0 * a));
	return (t);
}

float			ft_intersect_plane(t_ray ray, t_object *object)
{
	float t;

	(void)object;
	if (ray.direction.y == 0)
		t = -1;
	else
		t = -ray.position.y / ray.direction.y;
	return (t);
}
