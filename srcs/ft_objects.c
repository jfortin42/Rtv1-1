/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_objects.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/24 19:26:30 by ldedier           #+#    #+#             */
/*   Updated: 2018/06/26 19:19:19 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_object	*ft_new_sphere(void)
{
	t_object *res;

	if (!(res = malloc(sizeof(t_object))))
		return (NULL);
	res->color = 0xFF0000;
	res->object_union.sphere.radius = 1;
	res->position = ft_new_vec3(0, 0, 0);
	res->rotation = ft_new_vec3(0, 0, 0);
	res->intersect_func = &ft_intersect_sphere;
	res->normal_func = &ft_normal_sphere;
	res->smoothness = 0;
	res->shininess = 0;
	return (res);
}

t_object	*ft_new_cone(void)
{
	t_object *res;

	if (!(res = malloc(sizeof(t_object))))
		return (NULL);
	res->object_union.cone.angle = 1.5707 / 2;
	res->color = 0xFF0000;
	res->position = ft_new_vec3(0, 0, 0);
	res->rotation = ft_new_vec3(0, 0, 0);
	res->intersect_func = &ft_intersect_cone;
	res->normal_func = &ft_normal_cone;
	res->smoothness = 0;
	res->shininess = 0;
	return (res);
}

t_object	*ft_new_cylinder(void)
{
	t_object *res;

	if (!(res = malloc(sizeof(t_object))))
		return (NULL);
	res->object_union.cylinder.radius = 1;
	res->color = 0xFF0000;
	res->position = ft_new_vec3(0, 0, 0);
	res->rotation = ft_new_vec3(0, 0, 0);
	res->intersect_func = &ft_intersect_cylinder;
	res->normal_func = &ft_normal_cylinder;
	res->smoothness = 0;
	res->shininess = 0;
	return (res);
}

t_object	*ft_new_plane(void)
{
	t_object *res;

	if (!(res = malloc(sizeof(t_object))))
		return (NULL);
	res->color = 0xFF0000;
	res->position = ft_new_vec3(0, 0, 0);
	res->rotation = ft_new_vec3(0, 0, 0);
	res->intersect_func = &ft_intersect_plane;
	res->normal_func = &ft_normal_plane;
	res->smoothness = 0;
	res->shininess = 0;
	return (res);
}
