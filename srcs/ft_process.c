/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherriau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 13:16:12 by aherriau          #+#    #+#             */
/*   Updated: 2018/06/23 12:02:31 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	ft_process_4(t_env *e)
{
	if (e->keys.key_4)
		e->selected_object->rotation.x += M_PI / 16;
	if (e->keys.key_5)
		e->selected_object->rotation.x -= M_PI / 16;
	if (e->keys.key_7)
		e->selected_object->rotation.y += M_PI / 16;
	if (e->keys.key_8)
		e->selected_object->rotation.y -= M_PI / 16;
}

void	ft_process_3(t_env *e)
{
	if (e->keys.key_e)
		e->selected_object->rotation.z += M_PI / 16;
	if (e->keys.key_q)
		e->selected_object->rotation.z -= M_PI / 16;
	if (e->keys.key_o && e->can_change)
	{
		e->can_change = 0;
		e->current_object -= 1;
		if (e->current_object < 0)
			e->current_object = e->nb_objects - 1;
		e->selected_object = (t_object *)(ft_lst_at(e->objects,
					e->current_object)->content);
	}
	if (e->keys.key_p && e->can_change)
	{
		e->can_change = 0;
		e->current_object += 1;
		if (e->current_object >= e->nb_objects)
			e->current_object = 0;
		e->selected_object = (t_object *)(ft_lst_at(e->objects,
					e->current_object)->content);
	}
	ft_process_4(e);
}

void	ft_process_2(t_env *e)
{
	if (e->keys.key_d)
	{
		e->cam.position.x += cos(e->cam.rotation.x) * e->speed;
		e->cam.position.z += sin(e->cam.rotation.x) * e->speed;
	}
	if (e->keys.key_ctrl)
		e->cam.position.y -= e->speed;
	if (e->keys.key_space)
		e->cam.position.y += e->speed;
	if (e->keys.up)
		e->selected_object->position.y += e->speed;
	if (e->keys.down)
		e->selected_object->position.y -= e->speed;
	if (e->keys.right)
		e->selected_object->position.x += e->speed;
	if (e->keys.left)
		e->selected_object->position.x -= e->speed;
	if (e->keys.key_1)
		e->selected_object->position.z += e->speed;
	if (e->keys.key_2)
		e->selected_object->position.z -= e->speed;
	ft_process_3(e);
}

void	ft_process(t_env *e)
{
	if (e->keys.key_w)
	{
		e->cam.position.x -= sin(e->cam.rotation.x) * cos(e->cam.rotation.y)
			* e->speed;
		e->cam.position.y -= -sin(e->cam.rotation.y) * e->speed;
		e->cam.position.z += cos(e->cam.rotation.x) * cos(e->cam.rotation.y)
			* e->speed;
	}
	if (e->keys.key_s)
	{
		e->cam.position.x += sin(e->cam.rotation.x) * cos(e->cam.rotation.y)
			* e->speed;
		e->cam.position.y += -sin(e->cam.rotation.y) * e->speed;
		e->cam.position.z -= cos(e->cam.rotation.x) * cos(e->cam.rotation.y)
			* e->speed;
	}
	if (e->keys.key_a)
	{
		e->cam.position.x -= cos(e->cam.rotation.x) * e->speed;
		e->cam.position.z -= sin(e->cam.rotation.x) * e->speed;
	}
	ft_process_2(e);
}
