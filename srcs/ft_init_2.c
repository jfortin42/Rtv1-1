/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherriau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 12:34:10 by aherriau          #+#    #+#             */
/*   Updated: 2018/06/19 18:40:58 by ldedier          ###   ########.fr       */
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
	if (e->scene == 1)
	{
		ft_lstadd(&(e->objects), ft_lstnew_ptr(ft_new_plane(ft_new_vec3(0.f, -10.f, 0.f),
					ft_new_vec3(0.0f, 0.0, 0.0f), 0x444444), sizeof(t_object)));
		ft_lstadd(&(e->objects), ft_lstnew_ptr(ft_new_plane(ft_new_vec3(0.f, 30.f, 55.f),
					ft_new_vec3(0.0f, M_PI / 2, 0.0f), 0x0000ff), sizeof(t_object)));
		ft_lstadd(&(e->objects), ft_lstnew_ptr(ft_new_plane(ft_new_vec3(0.f, 10.f, 0.f),
					ft_new_vec3(0.0f, 0.0, 0.0f), 0x444444), sizeof(t_object)));
		ft_lstadd(&(e->objects), ft_lstnew_ptr(ft_new_cylinder(2.0, ft_new_vec3(-10.f, 0.f, 40.f),
					ft_new_vec3(0.0f, 0.0f, M_PI / 2), 0x777777), sizeof(t_object)));
		ft_lstadd(&(e->objects), ft_lstnew_ptr(ft_new_sphere(4.0, ft_new_vec3(-10.f, 10.f, 40.f),
					ft_new_vec3(0.0f, 0.0, 0.0f), 0x777777), sizeof(t_object)));
		ft_lstadd(&(e->objects), ft_lstnew_ptr(ft_new_sphere(4.0, ft_new_vec3(-10.f, -10.f, 40.f),
					ft_new_vec3(0.0f, 0.0, 0.0f), 0x777777), sizeof(t_object)));
		ft_lstadd(&(e->objects), ft_lstnew_ptr(ft_new_cylinder(2.0, ft_new_vec3(10.f, 0.f, 40.f),
					ft_new_vec3(0.0f, 0.0f, M_PI / 2), 0x777777), sizeof(t_object)));
		ft_lstadd(&(e->objects), ft_lstnew_ptr(ft_new_sphere(4.0, ft_new_vec3(10.f, 10.f, 40.f),
					ft_new_vec3(0.0f, 0.0, 0.0f), 0x777777), sizeof(t_object)));
		ft_lstadd(&(e->objects), ft_lstnew_ptr(ft_new_sphere(4.0, ft_new_vec3(10.f, -10.f, 40.f),
					ft_new_vec3(0.0f, 0.0, 0.0f), 0x777777), sizeof(t_object)));
		ft_lstadd(&(e->objects), ft_lstnew_ptr(ft_new_cylinder(2.0, ft_new_vec3(-10.f, 0.f,10.f),
					ft_new_vec3(0.0f, 0.0f, M_PI / 2), 0x777777), sizeof(t_object)));
		//100, 20
		ft_lstadd(&(e->objects), ft_lstnew_ptr(ft_new_sphere(4.0, ft_new_vec3(-10.f, 10.f, 10.f),
					ft_new_vec3(0.0f, 0.0, 0.0f), 0x777777), sizeof(t_object)));
		ft_lstadd(&(e->objects), ft_lstnew_ptr(ft_new_sphere(4.0, ft_new_vec3(-10.f, -10.f, 10.f),
					ft_new_vec3(0.0f, 0.0, 0.0f), 0x777777), sizeof(t_object)));
		ft_lstadd(&(e->objects), ft_lstnew_ptr(ft_new_cone(M_PI * 0.1, ft_new_vec3(10.f, 0.f, 10.f),
					ft_new_vec3(0.0f, 0, M_PI / 2), 0x0000ff), sizeof(t_object)));
		//100, 10
	//	ft_lstadd(&(e->objects), ft_lstnew_ptr(ft_new_sphere(10.0, ft_new_vec3(0.f, 10.f, 10.f),
	//				ft_new_vec3(0.0f, 0.0, 0.0f), 0xFF0000), sizeof(t_object)));
	}
	ft_lstadd(&(e->spots), ft_lstnew_ptr(ft_new_spot(ft_new_vec3(-10.f, 0.f, 5.f)), sizeof(t_spot)));
//	ft_lstadd(&(e->spots), ft_lstnew_ptr(ft_new_spot(ft_new_vec3(10.f, -4.f, 6.f)), sizeof(t_spot)));
	e->selected_object = (t_object *)(e->objects->content);
}
