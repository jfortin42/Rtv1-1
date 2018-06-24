/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherriau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 12:34:10 by aherriau          #+#    #+#             */
/*   Updated: 2018/06/24 23:33:00 by ldedier          ###   ########.fr       */
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

t_spot	*ft_new_spot(void)
{
	t_spot	*res;

	if (!(res = (t_spot *)malloc(sizeof(t_spot))))
		return (NULL);
	res->position = ft_new_vec3(0, 0, 0);
	return (res);
}

void	ft_init_scene(t_env *e)
{
	e->cam.fov = (70 * M_PI) / 180.0;
	e->speed = 0.2;
	e->ambiant_coefficient = 0.3;
	ft_init_keys(e);
	e->nb_objects = ft_lstlength(e->objects);
	e->current_object = 0;
	if(e->nb_objects)
		e->selected_object = (t_object *)(ft_lst_at(e->objects,
				e->current_object)->content);
	e->can_change = 1;
}
