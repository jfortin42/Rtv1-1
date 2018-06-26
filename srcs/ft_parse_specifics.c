/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_specifics.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/24 20:17:35 by ldedier           #+#    #+#             */
/*   Updated: 2018/06/26 17:16:32 by aherriau         ###   ########.fr       */
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
		ft_printf("this object does not have a radius attribute\n");
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
		ft_printf("this object does not have an angle attribute\n");
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
		ft_printf("this object does not have a shininess attribute\n");
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
		ft_printf("this object does not have a smoothness attribute\n");
		return (1);
	}
	*smoothness = ft_patof(&str);
	return (0);
}
