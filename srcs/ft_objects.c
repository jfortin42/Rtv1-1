/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_loop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 22:19:07 by ldedier           #+#    #+#             */
/*   Updated: 2018/06/19 14:53:50 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_object    *ft_new_sphere(float radius, t_vec3 pos, t_vec3 rot, int color)
{
	t_object *res;

	res = malloc(sizeof(t_object));
	res->color = color;
	res->object_union.sphere.radius = radius;
	res->position = pos;
	res->rotation = rot;
	res->intersect_func = &ft_intersect_sphere;	
	res->smoothness = 0;
	res->shininess = 0;
	return (res);
}

t_object    *ft_new_cone(float angle, t_vec3 pos, t_vec3 rot, int color)
{
	t_object *res;

	res = malloc(sizeof(t_object));
	res->object_union.cone.angle = angle;
	res->color = color;
	res->position = pos;
	res->rotation = rot;
	res->intersect_func = &ft_intersect_cone;
	res->smoothness = 0;
	res->shininess = 0;
	return (res);
}

t_object    *ft_new_cylinder(float radius, t_vec3 pos, t_vec3 rot, int color)
{
	t_object *res;

	res = malloc(sizeof(t_object));
	res->object_union.cylinder.radius = radius;
	res->color = color;
	res->position = pos;
	res->rotation = rot;
	res->intersect_func = &ft_intersect_cylinder;	
	res->smoothness = 0;
	res->shininess = 0;
	return (res);
}

t_object    *ft_new_plane(t_vec3 pos, t_vec3 rot, int color)
{
	t_object *res;

	res = malloc(sizeof(t_object));
	res->color = color;
	res->position = pos;
	res->rotation = rot;
	res->intersect_func = &ft_intersect_plane;
	res->smoothness = 0;
	res->shininess = 0;
	return (res);
}
