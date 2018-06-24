/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherriau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 21:30:03 by aherriau          #+#    #+#             */
/*   Updated: 2018/06/23 12:10:41 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	ft_scene_6_4(t_env *e)
{
	t_object	*obj;

	ft_lstadd(&(e->objects), ft_lstnew_ptr(ft_new_sphere(4.0, ft_new_vec3(10.f,
		-10.f, 10.f), ft_new_vec3(0.f, 0.f, 0.f), 0x777777), sizeof(t_object)));
	obj = (t_object *)(e->objects->content);
	obj->smoothness = 100;
	obj->shininess = 10;
	ft_lstadd(&(e->spots), ft_lstnew_ptr(ft_new_spot(ft_new_vec3(-20.f, -2.f,
		-10.f)), sizeof(t_spot)));
	ft_lstadd(&(e->spots), ft_lstnew_ptr(ft_new_spot(ft_new_vec3(20.f, -2.f,
		-10.f)), sizeof(t_spot)));
	ft_lstadd(&(e->objects), ft_lstnew_ptr(ft_new_cylinder(2.0,
		ft_new_vec3(10.f, 0.f, 10.f), ft_new_vec3(0.0f, 0.0f, M_PI / 2),
		0x777777), sizeof(t_object)));
	obj = (t_object *)(e->objects->content);
	obj->smoothness = 100;
	obj->shininess = 10;
}

void	ft_scene_6_3(t_env *e)
{
	t_object	*obj;

	ft_lstadd(&(e->objects), ft_lstnew_ptr(ft_new_sphere(4.0, ft_new_vec3(-10.f,
		10.f, 10.f), ft_new_vec3(0.f, 0.f, 0.f), 0x777777), sizeof(t_object)));
	obj = (t_object *)(e->objects->content);
	obj->smoothness = 100;
	obj->shininess = 10;
	ft_lstadd(&(e->objects), ft_lstnew_ptr(ft_new_sphere(4.0, ft_new_vec3(-10.f,
		-10.f, 10.f), ft_new_vec3(0.f, 0.f, 0.f), 0x777777), sizeof(t_object)));
	obj = (t_object *)(e->objects->content);
	obj->smoothness = 100;
	obj->shininess = 10;
	ft_lstadd(&(e->objects), ft_lstnew_ptr(ft_new_sphere(4.0, ft_new_vec3(10.f,
		10.f, 10.f), ft_new_vec3(0.f, 0.f, 0.f), 0x777777), sizeof(t_object)));
	obj = (t_object *)(e->objects->content);
	obj->smoothness = 100;
	obj->shininess = 10;
	ft_lstadd(&(e->objects), ft_lstnew_ptr(ft_new_sphere(1.f, ft_new_vec3(0.f,
		-8.f, 12.f), ft_new_vec3(0.f, 0.f, 0.f), 0xff0000), sizeof(t_object)));
	obj = (t_object *)(e->objects->content);
	obj->smoothness = 100;
	obj->shininess = 10;
	ft_scene_6_4(e);
}

void	ft_scene_6_2(t_env *e)
{
	t_object	*obj;

	ft_lstadd(&(e->objects), ft_lstnew_ptr(ft_new_cylinder(2.0,
		ft_new_vec3(10.f, 0.f, 40.f), ft_new_vec3(0.0f, 0.0f, M_PI / 2),
		0x777777), sizeof(t_object)));
	obj = (t_object *)(e->objects->content);
	obj->smoothness = 100;
	obj->shininess = 10;
	ft_lstadd(&(e->objects), ft_lstnew_ptr(ft_new_sphere(4.0, ft_new_vec3(10.f,
		10.f, 40.f), ft_new_vec3(0.f, 0.f, 0.f), 0x777777), sizeof(t_object)));
	obj = (t_object *)(e->objects->content);
	obj->smoothness = 100;
	obj->shininess = 10;
	ft_lstadd(&(e->objects), ft_lstnew_ptr(ft_new_sphere(4.0, ft_new_vec3(10.f,
		-10.f, 40.f), ft_new_vec3(0.f, 0.f, 0.f), 0x777777), sizeof(t_object)));
	obj = (t_object *)(e->objects->content);
	obj->smoothness = 100;
	obj->shininess = 10;
	ft_lstadd(&(e->objects), ft_lstnew_ptr(ft_new_cylinder(2.0,
		ft_new_vec3(-10.f, 0.f, 10.f), ft_new_vec3(0.f, 0.f, M_PI / 2),
		0x777777), sizeof(t_object)));
	obj = (t_object *)(e->objects->content);
	obj->smoothness = 100;
	obj->shininess = 10;
	ft_scene_6_3(e);
}

void	ft_scene_6(t_env *e)
{
	t_object	*obj;

	ft_lstadd(&(e->objects), ft_lstnew_ptr(ft_new_plane(ft_new_vec3(0.f, -10.f,
		0.f), ft_new_vec3(0.0f, 0.0, 0.0f), 0x888888), sizeof(t_object)));
	ft_lstadd(&(e->objects), ft_lstnew_ptr(ft_new_plane(ft_new_vec3(0.f, 30.f,
		55.f), ft_new_vec3(0.0f, M_PI / 2, 0.0f), 0x0000ff), sizeof(t_object)));
	ft_lstadd(&(e->objects), ft_lstnew_ptr(ft_new_plane(ft_new_vec3(0.f, 10.f,
		0.f), ft_new_vec3(0.0f, 0.0, 0.0f), 0x222222), sizeof(t_object)));
	ft_lstadd(&(e->objects), ft_lstnew_ptr(ft_new_cylinder(2.0,
		ft_new_vec3(-10.f, 0.f, 40.f), ft_new_vec3(0.0f, 0.0f, M_PI / 2),
		0x777777), sizeof(t_object)));
	obj = (t_object *)(e->objects->content);
	obj->smoothness = 100;
	obj->shininess = 10;
	ft_lstadd(&(e->objects), ft_lstnew_ptr(ft_new_sphere(4.0, ft_new_vec3(-10.f,
		10.f, 40.f), ft_new_vec3(0.f, 0.f, 0.f), 0x777777), sizeof(t_object)));
	obj = (t_object *)(e->objects->content);
	obj->smoothness = 100;
	obj->shininess = 10;
	ft_lstadd(&(e->objects), ft_lstnew_ptr(ft_new_sphere(4.0, ft_new_vec3(-10.f,
		-10.f, 40.f), ft_new_vec3(0.f, 0.f, 0.f), 0x777777), sizeof(t_object)));
	obj = (t_object *)(e->objects->content);
	obj->smoothness = 100;
	obj->shininess = 10;
	ft_scene_6_2(e);
}
