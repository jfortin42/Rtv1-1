/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 21:04:53 by ldedier           #+#    #+#             */
/*   Updated: 2018/04/08 19:27:18 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_OBJECTS_H
# include "libmat.h"

typedef struct		s_sphere
{
					float radius;
					t_vec3	position;
					t_vec3	rotation;
					t_vec3	scale;
					int		color;
}					t_sphere;

#endif
