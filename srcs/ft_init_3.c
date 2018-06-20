/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherriau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 21:28:28 by aherriau          #+#    #+#             */
/*   Updated: 2018/06/20 21:29:55 by aherriau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	ft_scene_3(t_env *e)
{
	ft_lstadd(&(e->objects), ft_lstnew_ptr(ft_new_cylinder(5.0,
					ft_new_vec3(0.f, 0.f, 10.f), ft_new_vec3(0.0f, 0.0f,
						M_PI / 2), 0x00ff00), sizeof(t_object)));
	ft_lstadd(&(e->spots), ft_lstnew_ptr(ft_new_spot(ft_new_vec3(10.f, 0.f,
						0.f)), sizeof(t_spot)));
}

void	ft_scene_4(t_env *e)
{
	ft_lstadd(&(e->objects), ft_lstnew_ptr(ft_new_cone(M_PI * 0.2,
					ft_new_vec3(0.f, 0.f, 0.f), ft_new_vec3(0.0f, 0.0f,
						M_PI / 2), 0xffff00), sizeof(t_object)));
	ft_lstadd(&(e->spots), ft_lstnew_ptr(ft_new_spot(ft_new_vec3(10.f, 0.f,
						-10.f)), sizeof(t_spot)));
}

void	ft_scene_5(t_env *e)
{
	t_object	*obj;

	ft_lstadd(&(e->objects), ft_lstnew_ptr(ft_new_plane(ft_new_vec3(0.f, -10.f,
		0.f), ft_new_vec3(0.0f, 0.0f, 0.0f), 0x444444), sizeof(t_object)));
	ft_lstadd(&(e->objects), ft_lstnew_ptr(ft_new_plane(ft_new_vec3(0.f, 30.f,
		55.f), ft_new_vec3(0.0f, M_PI / 2, 0.0f), 0x0000ff), sizeof(t_object)));
	ft_lstadd(&(e->objects), ft_lstnew_ptr(ft_new_sphere(5.0, ft_new_vec3(0.f,
		-6.5f, 20.f), ft_new_vec3(0.f, 0.f, 0.f), 0xff0000), sizeof(t_object)));
	obj = (t_object *)(e->objects->content);
	obj->smoothness = 50;
	obj->shininess = 10;
	ft_lstadd(&(e->objects), ft_lstnew_ptr(ft_new_cylinder(5.0,
		ft_new_vec3(-3.f, 0.f, 24.f), ft_new_vec3(0.0f, 0.0f, M_PI / 4),
		0x00ff00), sizeof(t_object)));
	ft_lstadd(&(e->objects), ft_lstnew_ptr(ft_new_cone(M_PI * 0.22,
		ft_new_vec3(7.f, -5.f, 20.f), ft_new_vec3(0.0f, 0.0f, -M_PI / 3),
		0xffff00), sizeof(t_object)));
	ft_lstadd(&(e->spots), ft_lstnew_ptr(ft_new_spot(ft_new_vec3(10.f, 0.f,
		0.f)), sizeof(t_spot)));
}
