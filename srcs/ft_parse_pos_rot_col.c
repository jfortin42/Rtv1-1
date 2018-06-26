/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_pos_rot_col.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/24 20:05:26 by ldedier           #+#    #+#             */
/*   Updated: 2018/06/26 16:40:09 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		ft_parse_rot_vec(t_vec3 *rot, char *str, t_env *e)
{
	rot->x = ft_deg_to_rad(ft_patof(&str));
	if (e->parser.parsed_object == CAMERA)
		rot->y = ft_deg_to_rad(ft_fclamp( -90, ft_patof(&str), 90));
	else
		rot->y = ft_deg_to_rad(ft_patof(&str));
	if (e->parser.parsed_object != CAMERA)
		rot->z = ft_deg_to_rad(ft_patof(&str));
	return (0);
}

int		ft_parse_rot(char *str, t_env *e)
{
	t_vec3 *rot;

	if (e->parser.parsed_object == CAMERA)
		rot = &(e->cam.rotation);
	else if (e->parser.parsed_object != LIGHT)
		rot = &(((t_object*)(e->objects->content))->rotation);
	else
	{
		ft_printf(
		"line %d: current object does not have a rotation attribute\n",
			e->parser.nb_lines);
		return (1);
	}
	return (ft_parse_rot_vec(rot, str, e));
}


int		ft_parse_pos(char *str, t_env *e)
{
	t_vec3 *pos;

	if (e->parser.parsed_object == CAMERA)
		pos = &(e->cam.position);
	else if (e->parser.parsed_object != LIGHT)
		pos = &(((t_object*)(e->objects->content))->position);
	else
		pos = &(((t_spot*)(e->spots->content))->position);
	pos->x = ft_patof(&str);
	pos->y = ft_patof(&str);
	pos->z = ft_patof(&str);
	return (0);
}

int		ft_parse_col_vec(t_ivec3 vec, int *col, t_env *e)
{
	if (vec.x > 255 || vec.x < 0 || vec.y > 255 || vec.y < 0 ||
		vec.z > 255 || vec.z < 0)
	{
		ft_printf(
		"line %d: (%d, %d, %d) : invalid color \n",
			vec.x, vec.y, vec.z, e->parser.nb_lines);
		return (1);
	}
	*col = (vec.x << 16) | (vec.y << 8) | (vec.z);
	return (0);

}

int		ft_parse_col(char *str, t_env *e)
{
	int *col;
	t_ivec3 vec;

	if (e->parser.parsed_object != CAMERA && e->parser.parsed_object != LIGHT)
		col = &(((t_object*)(e->objects->content))->color);
	else
	{
		ft_printf(
		"line %d: current object does not have a color attribute\n",
			e->parser.nb_lines);
		return (1);
	}
	vec.x = ft_patoi(&str);
	vec.y = ft_patoi(&str);
	vec.z = ft_patoi(&str);
	return (ft_parse_col_vec(vec, col, e));
}
