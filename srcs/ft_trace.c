/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 21:04:27 by ldedier           #+#    #+#             */
/*   Updated: 2018/06/23 12:14:38 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	ft_transform_ray(t_ray *ray, t_object *object, t_ray save)
{
	ray->position = ft_vec3_mat4_mult(save.position, object->transform_pos_inv);
	ray->direction =
		ft_vec3_mat4_mult(save.direction, object->transform_dir_inv);
	ft_vec3_normalize(&(ray->direction));
}

void	ft_process_hit(t_hit *hit, t_ray ray, float t, t_object *object)
{
	hit->t = t;
	hit->point = ft_vec3_add(ft_vec3_scalar(ray.direction, hit->t),
			ray.position);
	hit->normal = object->normal_func(hit->point,
			object);
	if (ft_dot_product(ray.direction, hit->normal) > 0)
		hit->normal = ft_vec3_scalar(hit->normal, -1);
	hit->world_point = ft_vec3_mat4_mult(hit->point,
			object->transform_pos);
	hit->world_normal = normalize(ft_vec3_mat4_mult(hit->normal,
			object->transform_dir));
	hit->object = object;
}

t_hit	ft_trace(t_ray ray, t_env *e)
{
	t_list		*ptr;
	t_object	*object;
	float		t;
	t_hit		hit;
	t_ray		save;

	save = ray;
	hit.t = -1;
	ptr = e->objects;
	while (ptr != NULL)
	{
		object = (t_object *)(ptr->content);
		ft_transform_ray(&ray, object, save);
		t = object->intersect_func(ray, object);
		if (t > 0 && (t < hit.t || hit.t == -1))
			ft_process_hit(&hit, ray, t, object);
		ptr = ptr->next;
	}
	return (hit);
}
