/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_specifics.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/24 20:17:35 by ldedier           #+#    #+#             */
/*   Updated: 2018/06/26 18:27:23 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		ft_parse_radius(char *str, t_env *e)
{
	float *radius;

	if (e->parser.parsed_object == SPHERE)
		radius = &(((t_object*)(e->objects->content))
				->object_union.sphere.radius);
	else if(e->parser.parsed_object == CYLINDER)
		radius = &(((t_object*)(e->objects->content))
				->object_union.cylinder.radius);
	else
	{
		ft_putendl("this object does not have a radius attribute");
		return (1);
	}
	*radius = ft_patof(&str);
	return (0);
}

int		ft_parse_angle(char *str, t_env *e)
{
	float *angle;

	if (e->parser.parsed_object == CONE)
		angle = &(((t_object*)(e->objects->content))
				->object_union.cone.angle);
	else
	{
		ft_putendl("this object does not have an angle attribute");
		return (1);
	}
	*angle = ft_deg_to_rad(ft_fclamp(1.0, ft_patof(&str), 89.0));
	return (0);
}


int		ft_parse_shine(char *str, t_env *e)
{
	float *shininess;

	if (e->parser.parsed_object != CAMERA &&
			e->parser.parsed_object != LIGHT)
		shininess = &(((t_object*)(e->objects->content))
				->shininess);
	else
	{
		ft_putendl("this object does not have a shininess attribute");
		return (1);
	}
	*shininess = ft_patof(&str);
	return (0);
}

int		ft_parse_smooth(char *str, t_env *e)
{
	float *smoothness;

	if (e->parser.parsed_object != CAMERA &&
			e->parser.parsed_object != LIGHT)
		smoothness = &(((t_object*)(e->objects->content))
				->smoothness);
	else
	{
		ft_putendl("this object does not have a smoothness attribute");
		return (1);
	}
	*smoothness = ft_patof(&str);
	return (0);
}

int		ft_parse_intensity(char *str, t_env *e)
{
	float *ambiant;

	if (e->parser.parsed_object == AMBIANT)
		ambiant = &(e->ambiant_coefficient);
	else
	{
		ft_putendl("this object does not have a intensity attribute");
		return (1);
	}
	*ambiant = ft_fclamp(0, ft_patof(&str), 1);
	printf("%f\n", *ambiant);
	return (0);
}
