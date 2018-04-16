/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libmath.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherriau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 14:19:04 by aherriau          #+#    #+#             */
/*   Updated: 2018/04/16 15:59:24 by aherriau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBMATH_H
# define LIBMATH_H

#include "math.h"

typedef struct	s_v2d
{
	float		x;
	float		y;
}				t_v2d;

typedef struct	s_v3d
{
	float		x;
	float		y;
	float		z;
}				t_v3d;

t_v3d			ft_new_zero_v3d(void);
t_v3d			ft_new_v3d(float x, float y, float z);
t_v3d			ft_plus_new_v3d(t_v3d v1, t_v3d v2);
void			ft_plus_v3d(t_v3d *v1, t_v3d v2);
t_v3d			ft_minus_new_v3d(t_v3d v1, t_v3d v2);

t_v3d			ft_cross_product_v3d(t_v3d v1, t_v3d v2);
t_v3d			ft_product_v3d(t_v3d v, float multiple);
t_v3d			ft_scale_new_v3d(t_v3d v, float multiple);
void			ft_scale_v3d(t_v3d *v, float multiple);
t_v3d			ft_reverse_v3d(t_v3d v);

float			ft_dot_product_v3d(t_v3d v1, t_v3d v2);
float			ft_magnitude_v3d(t_v3d v);
void			ft_normalize_v3d(t_v3d *v);
float			ft_square_length_v3d(t_v3d v);
t_v3d			ft_reflect_v3d(t_v3d v, t_v3d n);

#endif
