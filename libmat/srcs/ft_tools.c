/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 13:14:44 by ldedier           #+#    #+#             */
/*   Updated: 2018/06/19 15:00:28 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmat.h"
#include "stdio.h"
//TODELL
//
void	ft_print_vec3(t_vec3 vec)
{
	printf("x:%.2f\ny:%.2f\nz:%.2f\n", vec.x, vec.y, vec.z);
}
void	ft_print_mat4(t_mat4 mat)
{
	int i;
	int j;
	int k;

	i = 0;
	while (i < 4)
	{
		k = i;
		j = 0;
		while (j < 4)
		{
			printf("%.1f ", mat.as_mat[k]);
			k += 4;
			j++;
		}
		printf("\n");
		i++;
	}
	printf("\n");
}
