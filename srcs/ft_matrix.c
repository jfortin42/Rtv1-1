/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherriau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 13:17:10 by aherriau          #+#    #+#             */
/*   Updated: 2018/06/20 21:52:14 by aherriau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_mat4	ft_mat4_inv_translate(t_mat4 trans)
{
	int		i;

	i = 12;
	while (i < 15)
	{
		trans.as_mat[i] *= -1;
		i++;
	}
	return (trans);
}

void	ft_compute_matrix(t_object *object)
{
	t_mat4	rotate;
	t_mat4	rotate2;
	t_mat4	transform;
	t_mat4	translate;
	t_mat4	translate2;

	rotate = ft_mat4_mult(ft_mat4_rotate_x(object->rotation.y),
			ft_mat4_mult(ft_mat4_rotate_y(object->rotation.x),
				ft_mat4_rotate_z(object->rotation.z)));
	translate = ft_mat4_translate_vec(object->position);
	transform = ft_mat4_mult(translate, rotate);
	translate2 = ft_mat4_inv_translate(translate);
	rotate2 = ft_mat4_mult(ft_mat4_rotate_z(-object->rotation.z),
			ft_mat4_mult(ft_mat4_rotate_y(-object->rotation.x),
				ft_mat4_rotate_x(-object->rotation.y)));
	object->transform_pos = transform;
	object->transform_dir = rotate;
	object->transform_pos_inv = ft_mat4_mult(rotate2, translate2);
	object->transform_dir_inv = rotate2;
}

void	ft_compute_matrices_list(t_list *objects)
{
	t_list		*ptr;
	t_object	*object;

	ptr = objects;
	while (ptr != NULL)
	{
		object = (t_object *)(ptr->content);
		ft_compute_matrix(object);
		ptr = ptr->next;
	}
}
