/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 21:04:53 by ldedier           #+#    #+#             */
/*   Updated: 2018/04/14 18:47:07 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_OBJECTS_H
# include "libmat.h"

typedef struct		s_sphere
{
	float			radius;
}					t_sphere;

typedef struct		s_cone
{
	float			radius;
}					t_cone;

typedef struct		s_plane
{
	float			radius;
}					t_plane;

typedef struct		s_cylinder
{
	float			radius;
}					t_cylinder;
#endif
