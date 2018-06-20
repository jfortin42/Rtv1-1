/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 21:04:53 by ldedier           #+#    #+#             */
/*   Updated: 2018/06/20 22:10:37 by aherriau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_OBJECTS_H
# define FT_OBJECTS_H

# include "libmat.h"

typedef struct	s_sphere
{
	float		radius;
}				t_sphere;

typedef struct	s_plane
{
	float		norminette;
}				t_plane;

typedef struct	s_cone
{
	float		angle;
}				t_cone;

typedef struct	s_cylinder
{
	float		radius;
}				t_cylinder;
#endif
