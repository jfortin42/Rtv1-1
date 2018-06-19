/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherriau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 12:34:10 by aherriau          #+#    #+#             */
/*   Updated: 2018/06/19 19:25:18 by aherriau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	ft_init_keys(t_env *e)
{
	e->keys.up = 0;
	e->keys.down = 0;
	e->keys.left = 0;
	e->keys.right = 0;
	e->keys.key_o = 0;
	e->keys.key_p = 0;
	e->keys.key_7 = 0;
	e->keys.key_8 = 0;
	e->keys.key_5 = 0;
	e->keys.key_4 = 0;
	e->keys.key_2 = 0;
	e->keys.key_1 = 0;
	e->keys.key_w = 0;
	e->keys.key_a = 0;
	e->keys.key_s = 0;
	e->keys.key_d = 0;
	e->keys.key_e = 0;
	e->keys.key_q = 0;
	e->keys.key_ctrl = 0;
	e->keys.key_space = 0;
	e->keys.key_shift = 0;
}

t_spot	*ft_new_spot(t_vec3 position)
{
	t_spot	*res;

	res = (t_spot *)malloc(sizeof(t_spot));
	res->position = position;
	return (res);
}

void    ft_init_scene(t_env *e)
{
	e->objects = NULL;
	e->spots = NULL;
	e->cam.fov = (70 * M_PI) / 180.0;
	e->cam.position = ft_new_vec3(0, 0, -10);
	e->cam.rotation = ft_new_vec3(0 , 0, 0);
	e->speed = 0.2;
	e->ambiant_coefficient = 0.3;
	ft_init_keys(e);
	t_object *obj;
	if (e->scene == 1)
	{
		ft_lstadd(&(e->objects), ft_lstnew_ptr(ft_new_sphere(3.0, ft_new_vec3(0.f, 0.f, 0.f),
					ft_new_vec3(0.0f, 0.0f, 0.0f), 0xff0000), sizeof(t_object)));
		obj = (t_object *)(e->objects->content);
		obj->smoothness = 80;
		obj->shininess = 10;
		ft_lstadd(&(e->spots), ft_lstnew_ptr(ft_new_spot(ft_new_vec3(15.f, 2.f, -10.f)), sizeof(t_spot)));
	}
	else if (e->scene == 2)
	{
		ft_lstadd(&(e->objects), ft_lstnew_ptr(ft_new_plane(ft_new_vec3(0.f, -10.f, 0.f),
					ft_new_vec3(0.0f, 0.0f, 0.0f), 0x0000ff), sizeof(t_object)));
		obj = (t_object *)(e->objects->content);
		obj->smoothness = 80;
		obj->shininess = 10;
		ft_lstadd(&(e->spots), ft_lstnew_ptr(ft_new_spot(ft_new_vec3(-10.f, 10.f, -10.f)), sizeof(t_spot)));
	}
	else if (e->scene == 3)
	{
		ft_lstadd(&(e->objects), ft_lstnew_ptr(ft_new_cylinder(5.0, ft_new_vec3(0.f, 0.f, 0.f),
					ft_new_vec3(0.0f, 0.0f, M_PI / 2), 0x00ff00), sizeof(t_object)));
	}
	else if (e->scene == 4)
	{
		ft_lstadd(&(e->objects), ft_lstnew_ptr(ft_new_cone(M_PI * 0.1, ft_new_vec3(0.f, 0.f, 0.f),
					ft_new_vec3(0.0f, 0.0f, 0.0f), 0xffff00), sizeof(t_object)));
	}
	else if (e->scene == 5)
	{
		ft_lstadd(&(e->objects), ft_lstnew_ptr(ft_new_plane(ft_new_vec3(0.f, -10.f, 0.f),
					ft_new_vec3(0.0f, 0.0f, 0.0f), 0x444444), sizeof(t_object)));
		ft_lstadd(&(e->objects), ft_lstnew_ptr(ft_new_plane(ft_new_vec3(0.f, 30.f, 55.f),
					ft_new_vec3(0.0f, M_PI / 2, 0.0f), 0x0000ff), sizeof(t_object)));
		ft_lstadd(&(e->objects), ft_lstnew_ptr(ft_new_sphere(5.0, ft_new_vec3(0.f, -6.5f, 20.f),
					ft_new_vec3(0.0f, 0.0f, 0.0f), 0xff0000), sizeof(t_object)));
		obj = (t_object *)(e->objects->content);
		obj->smoothness = 50;
		obj->shininess = 10;
		ft_lstadd(&(e->objects), ft_lstnew_ptr(ft_new_cylinder(5.0, ft_new_vec3(-3.f, 0.f, 24.f),
					ft_new_vec3(0.0f, 0.0f, M_PI / 4), 0x00ff00), sizeof(t_object)));
		ft_lstadd(&(e->objects), ft_lstnew_ptr(ft_new_cone(M_PI * 0.22, ft_new_vec3(7.f, -5.f, 20.f),
					ft_new_vec3(0.0f, 0.0f, -M_PI / 3), 0xffff00), sizeof(t_object)));
		ft_lstadd(&(e->spots), ft_lstnew_ptr(ft_new_spot(ft_new_vec3(30.f, 0.f, 0.f)), sizeof(t_spot)));
	}
	else if (e->scene == 6)
	{
		ft_lstadd(&(e->objects), ft_lstnew_ptr(ft_new_plane(ft_new_vec3(0.f, -10.f, 0.f),
					ft_new_vec3(0.0f, 0.0, 0.0f), 0x888888), sizeof(t_object)));
		ft_lstadd(&(e->objects), ft_lstnew_ptr(ft_new_plane(ft_new_vec3(0.f, 30.f, 55.f),
					ft_new_vec3(0.0f, M_PI / 2, 0.0f), 0x0000ff), sizeof(t_object)));
		ft_lstadd(&(e->objects), ft_lstnew_ptr(ft_new_plane(ft_new_vec3(0.f, 10.f, 0.f),
					ft_new_vec3(0.0f, 0.0, 0.0f), 0x222222), sizeof(t_object)));
		ft_lstadd(&(e->objects), ft_lstnew_ptr(ft_new_cylinder(2.0, ft_new_vec3(-10.f, 0.f, 40.f),
					ft_new_vec3(0.0f, 0.0f, M_PI / 2), 0x777777), sizeof(t_object)));
		obj = (t_object *)(e->objects->content);
		obj->smoothness = 100;
		obj->shininess = 10;
		ft_lstadd(&(e->objects), ft_lstnew_ptr(ft_new_sphere(4.0, ft_new_vec3(-10.f, 10.f, 40.f),
					ft_new_vec3(0.0f, 0.0, 0.0f), 0x777777), sizeof(t_object)));
		obj = (t_object *)(e->objects->content);
		obj->smoothness = 100;
		obj->shininess = 10;
		ft_lstadd(&(e->objects), ft_lstnew_ptr(ft_new_sphere(4.0, ft_new_vec3(-10.f, -10.f, 40.f),
					ft_new_vec3(0.0f, 0.0, 0.0f), 0x777777), sizeof(t_object)));
		obj = (t_object *)(e->objects->content);
		obj->smoothness = 100;
		obj->shininess = 10;
		ft_lstadd(&(e->objects), ft_lstnew_ptr(ft_new_cylinder(2.0, ft_new_vec3(10.f, 0.f, 40.f),
					ft_new_vec3(0.0f, 0.0f, M_PI / 2), 0x777777), sizeof(t_object)));
		obj = (t_object *)(e->objects->content);
		obj->smoothness = 100;
		obj->shininess = 10;
		ft_lstadd(&(e->objects), ft_lstnew_ptr(ft_new_sphere(4.0, ft_new_vec3(10.f, 10.f, 40.f),
					ft_new_vec3(0.0f, 0.0, 0.0f), 0x777777), sizeof(t_object)));
		obj = (t_object *)(e->objects->content);
		obj->smoothness = 100;
		obj->shininess = 10;
		ft_lstadd(&(e->objects), ft_lstnew_ptr(ft_new_sphere(4.0, ft_new_vec3(10.f, -10.f, 40.f),
					ft_new_vec3(0.0f, 0.0, 0.0f), 0x777777), sizeof(t_object)));
		obj = (t_object *)(e->objects->content);
		obj->smoothness = 100;
		obj->shininess = 10;
		ft_lstadd(&(e->objects), ft_lstnew_ptr(ft_new_cylinder(2.0, ft_new_vec3(-10.f, 0.f,10.f),
					ft_new_vec3(0.0f, 0.0f, M_PI / 2), 0x777777), sizeof(t_object)));
		obj = (t_object *)(e->objects->content);
		obj->smoothness = 100;
		obj->shininess = 10;
		ft_lstadd(&(e->objects), ft_lstnew_ptr(ft_new_sphere(4.0, ft_new_vec3(-10.f, 10.f, 10.f),
					ft_new_vec3(0.0f, 0.0, 0.0f), 0x777777), sizeof(t_object)));
		obj = (t_object *)(e->objects->content);
		obj->smoothness = 100;
		obj->shininess = 10;
		ft_lstadd(&(e->objects), ft_lstnew_ptr(ft_new_sphere(4.0, ft_new_vec3(-10.f, -10.f, 10.f),
					ft_new_vec3(0.0f, 0.0, 0.0f), 0x777777), sizeof(t_object)));
		obj = (t_object *)(e->objects->content);
		obj->smoothness = 100;
		obj->shininess = 10;
		ft_lstadd(&(e->objects), ft_lstnew_ptr(ft_new_cylinder(2.0, ft_new_vec3(10.f, 0.f,10.f),
					ft_new_vec3(0.0f, 0.0f, M_PI / 2), 0x777777), sizeof(t_object)));
		obj = (t_object *)(e->objects->content);
		obj->smoothness = 100;
		obj->shininess = 10;
		ft_lstadd(&(e->objects), ft_lstnew_ptr(ft_new_sphere(4.0, ft_new_vec3(10.f, 10.f, 10.f),
					ft_new_vec3(0.0f, 0.0, 0.0f), 0x777777), sizeof(t_object)));
		obj = (t_object *)(e->objects->content);
		obj->smoothness = 100;
		obj->shininess = 10;
		ft_lstadd(&(e->objects), ft_lstnew_ptr(ft_new_sphere(4.0, ft_new_vec3(10.f, -10.f, 10.f),
					ft_new_vec3(0.0f, 0.0, 0.0f), 0x777777), sizeof(t_object)));
		obj = (t_object *)(e->objects->content);
		obj->smoothness = 100;
		obj->shininess = 10;
		ft_lstadd(&(e->objects), ft_lstnew_ptr(ft_new_sphere(1.f, ft_new_vec3(0.f, -8.f, 12.f),
						ft_new_vec3(0.0f, 0.0, 0.0f), 0xff0000), sizeof(t_object)));
		obj = (t_object *)(e->objects->content);
		obj->smoothness = 100;
		obj->shininess = 10;
	
		ft_lstadd(&(e->spots), ft_lstnew_ptr(ft_new_spot(ft_new_vec3(-20.f, -2.f, -10.f)), sizeof(t_spot)));
		ft_lstadd(&(e->spots), ft_lstnew_ptr(ft_new_spot(ft_new_vec3(20.f, -2.f, -10.f)), sizeof(t_spot)));
	}
	e->selected_object = (t_object *)(e->objects->content);
}
