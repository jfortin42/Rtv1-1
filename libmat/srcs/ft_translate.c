/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_translate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 00:42:09 by ldedier           #+#    #+#             */
/*   Updated: 2018/03/28 23:20:24 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmat.h"

t_mat4	ft_mat4_translate(float x, float y, float z)
{
	t_mat4 mat;

	mat.as_mat[0] = 1;
	mat.as_mat[1] = 0;
	mat.as_mat[2] = 0;
	mat.as_mat[3] = 0;

	mat.as_mat[4] = 0;
	mat.as_mat[5] = 1;
	mat.as_mat[6] = 0;
	mat.as_mat[7] = 0;

	mat.as_mat[8] = 0;
	mat.as_mat[9] = 0;
	mat.as_mat[10] = 1;
	mat.as_mat[11] = 0;

	mat.as_mat[12] = x;
	mat.as_mat[13] = y;
	mat.as_mat[14] = z;
	mat.as_mat[15] = 1;
	return(mat);
}